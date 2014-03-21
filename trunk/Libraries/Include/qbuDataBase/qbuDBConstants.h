#ifndef __SMDBCONSTANTS_H__
#define __SMDBCONSTANTS_H__

namespace smdb {
	enum InsertMode {
		IM_NO_EXTRA_HANDLING	= 0,
		IM_ROLLBACK				= 1,
		IM_ABORT				= 2,
		IM_REPLACE				= 3,
		IM_FAIL					= 4,
		IM_IGNORE				= 5
	};

}; //namespace smdb

#endif //__SMDBCONSTANTS_H__