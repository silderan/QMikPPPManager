#ifndef UNITTESTS_H
#define UNITTESTS_H

#ifndef QT_NO_DEBUG

#define UT_COMPARE(a,b)	(qWarning( (a==b) ? "PASS: "#a"=="#b : "FAIL: "#a"=="#b ) )

//#define UNIT_TESTS_UTILS
#define SIMULATE_ROS_INPUTS

#endif // QT_NO_DEBUG

#endif // UNITTESTS_H
