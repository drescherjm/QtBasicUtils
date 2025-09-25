#This file contains the automated unit testing for QtBasicUtils

if (QBU_BUILD_DATABASE)
	add_test(NAME DBSingleQuote0     COMMAND $<TARGET_FILE:BasicTest> +DBSINGLEQUOTE  --Quote_Expected- 10)
	
	add_test(NAME DBSingleQuote0_WF     	 COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected+ 10)	
	SET_TESTS_PROPERTIES(DBSingleQuote0_WF PROPERTIES WILL_FAIL TRUE)
	add_test(NAME DBSingleQuote1    	 	COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected- "10")	
	add_test(NAME DBSingleQuote1_WF     	 COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected+ "10")	
	SET_TESTS_PROPERTIES(DBSingleQuote1_WF PROPERTIES WILL_FAIL TRUE)
	add_test(NAME DBSingleQuote2     	 COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected+ "John Drescher")	
	add_test(NAME DBSingleQuote2_WF     	 COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected- "John Drescher")	
	SET_TESTS_PROPERTIES(DBSingleQuote2_WF PROPERTIES WILL_FAIL TRUE)
	add_test(NAME DBSingleQuote3     	 COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected+ "John")	
	add_test(NAME DBSingleQuote3_WF     	 COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected- "John")	
	SET_TESTS_PROPERTIES(DBSingleQuote3_WF PROPERTIES WILL_FAIL TRUE)
	add_test(NAME DBSingleQuote4    	 	COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected- "10.1")	
	add_test(NAME DBSingleQuote4_WF     	 COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected+ "10.4")	
	SET_TESTS_PROPERTIES(DBSingleQuote4_WF PROPERTIES WILL_FAIL TRUE)
	add_test(NAME DBSingleQuote5    	 	COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected- "-10.5")	
	add_test(NAME DBSingleQuote5_WF     	 COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected+ "-10.4")	
	SET_TESTS_PROPERTIES(DBSingleQuote5_WF PROPERTIES WILL_FAIL TRUE)
	add_test(NAME DBSingleQuote6    	 	COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected+ "10-33")	
	add_test(NAME DBSingleQuote6_WF     	 COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected- "10-42")	
	SET_TESTS_PROPERTIES(DBSingleQuote6_WF PROPERTIES WILL_FAIL TRUE)
	add_test(NAME DBSingleQuote7    	 	COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected+ "10.20.96.1")	
	add_test(NAME DBSingleQuote7_WF     	 COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected- "10.20.96.1")	
	SET_TESTS_PROPERTIES(DBSingleQuote7_WF PROPERTIES WILL_FAIL TRUE)
	
	add_test(NAME DBSingleQuote8    	 	COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected- -10)	
	add_test(NAME DBSingleQuote8_WF     	 COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected+ -10)	
	SET_TESTS_PROPERTIES(DBSingleQuote8_WF PROPERTIES WILL_FAIL TRUE)
	
	add_test(NAME DBSingleQuote9    	 	COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected- "-10")	
	add_test(NAME DBSingleQuote9_WF     	 COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected+ "-10")	
	SET_TESTS_PROPERTIES(DBSingleQuote9_WF PROPERTIES WILL_FAIL TRUE)	
	
	add_test(NAME DBSingleQuote10   	 	COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected+ "\" \"")	
	
	add_test(NAME DBSingleQuote11   	 	COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected- "(10+1)")	
	
	add_test(NAME DBSingleQuote12   	 	COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected+ "(-)")
	add_test(NAME DBSingleQuote13   	 	COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected- "(-1)")
	
	add_test(NAME DBSingleQuote14   	 	COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected+ "brca(-)")
	
	add_test(NAME DBSingleQuote15   	 	COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected- "max(a)")
	add_test(NAME DBSingleQuote16   	 	COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected- "count(*)")
	
	add_test(NAME DBSingleQuote17   	 	COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected- "like(X,Y)")
	
	add_test(NAME DBSingleQuote18   	 	COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected- "sqlite_version()")
	
	add_test(NAME DBSingleQuote19   	 	COMMAND BasicTest +DBSINGLEQUOTE  --Quote_Expected- "brca(-1)")
	
endif()

add_test(NAME StringOpts0		COMMAND BasicTest +UT  +STRINGOPT2 --S0="Test" --S1='John Drescher')
SET_TESTS_PROPERTIES(StringOpts0 PROPERTIES WILL_FAIL TRUE)

add_test(NAME StringOpts1		COMMAND BasicTest +UT  +STRINGOPT2 --S0="Check Mate" --S1="John Drescher")

file(WRITE ${EXECUTABLE_OUTPUT_PATH}/testStringOpts2.txt "+STRINGOPT2 --S0=\"Check Mate\" --S1=\"John Drescher\"")
add_test(NAME StringOpts2		COMMAND BasicTest +UT @${EXECUTABLE_OUTPUT_PATH}/testStringOpts2.txt )

file(WRITE ${EXECUTABLE_OUTPUT_PATH}/testStringOpts3.txt "+STRINGOPT2 --S0=\"Check Mate\" --S1='John Drescher'")
add_test(NAME StringOpts3		COMMAND BasicTest +UT @${EXECUTABLE_OUTPUT_PATH}/testStringOpts3.txt )


file(WRITE ${EXECUTABLE_OUTPUT_PATH}/testSetVar0.txt "+SET --group=\"Application\" --name=\"Current Study\" \"100\"" )
add_test(NAME SetVariable0		COMMAND BasicTest +UT @${EXECUTABLE_OUTPUT_PATH}/testSetVar0.txt )

file(WRITE ${EXECUTABLE_OUTPUT_PATH}/testSetVar1.txt "+SET --group=\"Application\" --name=\"Image Root\" \"J:/images/clean/Procesed Images/Breast/2011_MM_Study/Study100Set\"" )
add_test(NAME SetVariable1		COMMAND BasicTest +UT @${EXECUTABLE_OUTPUT_PATH}/testSetVar1.txt )


file(WRITE ${EXECUTABLE_OUTPUT_PATH}/test0.txt "+FLOATARGS 1.0 2.0 2.0 2.0 2.0 -S9.0")

add_test(NAME InvalidOpt0 		COMMAND BasicTest +UT +INVALIDCMDOPT --tests=BADADDOPT0 . )
SET_TESTS_PROPERTIES(InvalidOpt0 PROPERTIES WILL_FAIL TRUE)

add_test(NAME InvalidOpt1 		COMMAND BasicTest +UT +INVALIDCMDOPT --tests=BADADDOPT1 . )
SET_TESTS_PROPERTIES(InvalidOpt1 PROPERTIES WILL_FAIL TRUE)

add_test(NAME InvalidOpt2 		COMMAND BasicTest +UT +INVALIDCMDOPT --tests=GOODADDOPT0 . )


#add_test(FileCMD0	COMMAND BasicTest +UT  @${EXECUTABLE_OUTPUT_PATH}/test0.txt)

#This will fail because the file should not exist.
#add_test(FileCMD1	COMMAND BasicTest +UT  @${EXECUTABLE_OUTPUT_PATH}/../test111111111111111111.txt)
#SET_TESTS_PROPERTIES(FileCMD1 PROPERTIES WILL_FAIL TRUE)

add_test(NAME Test0			COMMAND BasicTest +UT  +?)
add_test(NAME Test1			COMMAND BasicTest +UT  +Test 1.0)
add_test(NAME StringListArg0  COMMAND BasicTest +UT  +STRLSTARG 1 2 3 4 . -S10)
add_test(NAME StringListArg1  COMMAND BasicTest +UT  +STRLSTARG 1 2 3 . -S6)
add_test(NAME StringListOpt0  COMMAND BasicTest +UT  +STRLSTOPT -I1 2 3 . -S6)
add_test(NAME StringListOpt1  COMMAND BasicTest +UT  +STRLSTOPT -I1 2 3 4 . -S10)

add_test(NAME PropMap0 		 COMMAND BasicTest +UT  +PROPMAP 0)
add_test(NAME PropMap1 		 COMMAND BasicTest +UT  +PROPMAP 1)

add_test(NAME BoolOpt1 		 COMMAND BasicTest +UT  +BOOLOPT -B)
add_test(NAME BoolOpt2 		 COMMAND BasicTest +UT  +BOOLOPT -B-)
SET_TESTS_PROPERTIES(BoolOpt2 PROPERTIES WILL_FAIL TRUE)

add_test(NAME ExtBoolOpt1 		 COMMAND BasicTest +UT  +EXTBOOLOPT --use_extended=+)
add_test(NAME ExtBoolOpt2 		 COMMAND BasicTest +UT  +EXTBOOLOPT --use_extended=-)
add_test(NAME ExtBoolOpt3 		 COMMAND BasicTest +UT  +EXTBOOLOPT --use_extended+)
add_test(NAME ExtBoolOpt4 		 COMMAND BasicTest +UT  +EXTBOOLOPT --use_extended-)
add_test(NAME ExtBoolOpt5 		 COMMAND BasicTest +UT  +EXTBOOLOPT --use_extended)
SET_TESTS_PROPERTIES(ExtBoolOpt2 PROPERTIES WILL_FAIL TRUE)
SET_TESTS_PROPERTIES(ExtBoolOpt4 PROPERTIES WILL_FAIL TRUE)

add_test(NAME FloatArgs0	     COMMAND BasicTest +UT  +FLOATARGS 1.0 -S5.0)
add_test(NAME FloatArgs1	     COMMAND BasicTest +UT  +FLOATARGS 2.0 -S6.0)
add_test(NAME FloatArgs2	     COMMAND BasicTest +UT  +FLOATARGS 1.0 1.0 -S5.0)
add_test(NAME FloatArgs3	     COMMAND BasicTest +UT  +FLOATARGS 1.0 2.0 -S6.0)
add_test(NAME FloatArgs4	     COMMAND BasicTest +UT  +FLOATARGS 1.0 1.0 1.0 1.0 1.0 -S5.0)
add_test(NAME FloatArgs5	     COMMAND BasicTest +UT  +FLOATARGS 2.0 2.0 2.0 2.0 2.0 -S10.0)	
add_test(NAME FloatArgs6	     COMMAND BasicTest +UT  +FLOATARGS -2.0 2.0 2.0 2.0 2.0 -S6.0)

add_test(NAME FloatArgs7	     COMMAND BasicTest +UT  +FLOATARGS 1.0 2.0 2.0 2.0 2.0 -S10.0)	
SET_TESTS_PROPERTIES(FloatArgs7 PROPERTIES WILL_FAIL TRUE)

add_test(NAME FloatArgs8	     COMMAND BasicTest +UT  +FLOATARGS 1.0 2.0 2.0 2.0 2.0 1.0 -S10.0)	
SET_TESTS_PROPERTIES(FloatArgs8 PROPERTIES WILL_FAIL TRUE)

add_test(NAME DoubleArgs0	     COMMAND BasicTest +UT  +DOUBLEARGS 1.0 -S5.0)
add_test(NAME DoubleArgs1	     COMMAND BasicTest +UT  +DOUBLEARGS 2.0 -S6.0)
add_test(NAME DoubleArgs2	     COMMAND BasicTest +UT  +DOUBLEARGS 1.0 1.0 -S5.0)
add_test(NAME DoubleArgs3	     COMMAND BasicTest +UT  +DOUBLEARGS 1.0 2.0 -S6.0)
add_test(NAME DoubleArgs4	     COMMAND BasicTest +UT  +DOUBLEARGS 1.0 1.0 1.0 1.0 1.0 -S5.0)
add_test(NAME DoubleArgs5	     COMMAND BasicTest +UT  +DOUBLEARGS 2.0 2.0 2.0 2.0 2.0 -S10.0)	
add_test(NAME DoubleArgs6	     COMMAND BasicTest +UT  +DOUBLEARGS -2.0 2.0 2.0 2.0 2.0 -S6.0)

add_test(NAME DoubleArgs7	     COMMAND BasicTest +UT  +DOUBLEARGS 1.0 2.0 2.0 2.0 2.0 -S10.0)	
SET_TESTS_PROPERTIES(DoubleArgs7 PROPERTIES WILL_FAIL TRUE)

add_test(NAME DoubleArgs8	     COMMAND BasicTest +UT  +DOUBLEARGS 1.0 2.0 2.0 2.0 2.0 1.0 -S10.0)	
SET_TESTS_PROPERTIES(DoubleArgs8 PROPERTIES WILL_FAIL TRUE)



# Test XML Classes..

add_test(NAME XMLExport0	     	 COMMAND BasicTest +UT  +XMLEXP 0)	
add_test(NAME XMLExport1	     	 COMMAND BasicTest +UT  +XMLEXP 1)	
add_test(NAME XMLExport2	     	 COMMAND BasicTest +UT  +XMLEXP 2)	
add_test(NAME XMLExport3	     	 COMMAND BasicTest +UT  +XMLEXP 3)	
add_test(NAME XMLExport4	     	 COMMAND BasicTest +UT  +XMLEXP 4)	
add_test(NAME XMLExport5	     	 COMMAND BasicTest +UT  +XMLEXP 5)	
add_test(NAME XMLExport6	     	 COMMAND BasicTest +UT  +XMLEXP 6)	
add_test(NAME XMLExport7	     	 COMMAND BasicTest +UT  +XMLEXP 7)	
add_test(NAME XMLExport8	     	 COMMAND BasicTest +UT  +XMLEXP 8)
add_test(NAME XMLExport9     	 COMMAND BasicTest +UT  +XMLEXP 9)
SET_TESTS_PROPERTIES(XMLExport9 PROPERTIES WILL_FAIL TRUE)
add_test(NAME XMLExport10	     COMMAND BasicTest +UT  +XMLEXP 10)
add_test(NAME XMLExport11	     COMMAND BasicTest +UT  +XMLEXP 11)

add_test(NAME XMLImport0	     	 COMMAND BasicTest +UT  +XMLIMP 0)	

add_test(NAME XMLPerformance0   	 COMMAND BasicTest +UT  +XMLPERF 0)	

add_test(NAME UserProp0	     	 COMMAND BasicTest +UT  +USERPROP 0)	
add_test(NAME UserProp1	     	 COMMAND BasicTest +UT  +USERPROP 1)	
add_test(NAME UserProp2	     	 COMMAND BasicTest +UT  +USERPROP 2)	
add_test(NAME UserProp3	     	 COMMAND BasicTest +UT  +USERPROP 3)	
SET_TESTS_PROPERTIES(UserProp3 PROPERTIES WILL_FAIL TRUE)

add_test(NAME UserProp4	     	 COMMAND BasicTest +UT  +USERPROP 4)	
SET_TESTS_PROPERTIES(UserProp4 PROPERTIES WILL_FAIL TRUE)

add_test(NAME UserProp5	     	 COMMAND BasicTest +UT  +USERPROP 5)	
add_test(NAME UserProp6	     	 COMMAND BasicTest +UT  +USERPROP 6)	
add_test(NAME UserProp7	     	 COMMAND BasicTest +UT  +USERPROP 7)	
add_test(NAME UserProp8_PropMap_operator=			COMMAND BasicTest +UT  +USERPROP 8)	
add_test(NAME UserProp9_PropList_operator=	  		COMMAND BasicTest +UT  +USERPROP 9)	
add_test(NAME UserProp10	     	 COMMAND BasicTest +UT  +USERPROP 10)	
add_test(NAME UserProp11	     	 COMMAND BasicTest +UT  +USERPROP 11)	
