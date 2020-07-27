#pragma once

#ifndef QBUDBCONSTANTS_H
#define QBUDBCONSTANTS_H

namespace qbudb {
	enum InsertMode {
		IM_NO_EXTRA_HANDLING = 0,
		IM_ROLLBACK          = 1,
		IM_ABORT             = 2,
		IM_REPLACE           = 3,
		IM_FAIL              = 4,
		IM_IGNORE            = 5
	};

	enum JoinFlag {
		JF_SINGLE_SOURCE = 1,
		JF_LEFT_JOIN,
		JF_LEFT_OUTER_JOIN,
		JF_NATURAL_LEFT_JOIN,
		JF_NATURAL_LEFT_OUTER_JOIN,
		JF_NATURAL_JOIN,
		JF_JOIN,
		JF_CROSS_JOIN,
		JF_NATURAL_CROSS_JOIN,
		JF_DEFAULT = JF_SINGLE_SOURCE,
	};
}; //namespace qbudb

#endif // QBUDBCONSTANTS_H

