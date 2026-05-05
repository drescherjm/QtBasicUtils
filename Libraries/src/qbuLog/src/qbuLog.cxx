#include "qbuLogPCH.h"
#include "qbuLog/qbuLog.h"
#include <QRegularExpression>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QString logFileName(QString strFile, int nLine)
{
	QRegularExpression regex(R"(\.\.[/\\])"); // Matches "..\" or "../"
	strFile.remove(regex);
	return QString("%1:%2").arg(strFile).arg(nLine);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) || defined(_WIN32)
#define NOMINMAX
#include <windows.h>
inline bool isDebuggerPresent() {
	return IsDebuggerPresent();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#elif defined(__APPLE__)
#include <sys/sysctl.h>
#include <unistd.h>
inline bool isDebuggerPresent() {
	int               mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PID, getpid()};
	struct kinfo_proc info{};
	size_t            size = sizeof(info);
	sysctl(mib, 4, &info, &size, nullptr, 0);
	return (info.kp_proc.p_flag & P_TRACED) != 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#elif defined(__linux__)
#include <fstream>
inline bool isDebuggerPresent() {
	// /proc/self/status contains "TracerPid: N"
	// N is 0 if no debugger, non-zero if a debugger is attached
	std::ifstream status("/proc/self/status");
	for (std::string line; std::getline(status, line);) {
		if (line.rfind("TracerPid:", 0) == 0) {
			int pid = std::stoi(line.substr(10));
			return pid != 0;
		}
	}
	return false;
}

#else
// Fallback: assume no debugger
inline bool isDebuggerPresent() {
	return false;
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
