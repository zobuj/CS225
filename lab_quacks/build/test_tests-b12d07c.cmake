add_test( sumDigits /workspaces/cs225/release-f22/release-f22/lab_quacks/build/test sumDigits  )
set_tests_properties( sumDigits PROPERTIES WORKING_DIRECTORY /workspaces/cs225/release-f22/release-f22/lab_quacks/build)
add_test( triangle /workspaces/cs225/release-f22/release-f22/lab_quacks/build/test triangle  )
set_tests_properties( triangle PROPERTIES WORKING_DIRECTORY /workspaces/cs225/release-f22/release-f22/lab_quacks/build)
add_test( sum /workspaces/cs225/release-f22/release-f22/lab_quacks/build/test sum  )
set_tests_properties( sum PROPERTIES WORKING_DIRECTORY /workspaces/cs225/release-f22/release-f22/lab_quacks/build)
add_test( isBalanced /workspaces/cs225/release-f22/release-f22/lab_quacks/build/test isBalanced  )
set_tests_properties( isBalanced PROPERTIES WORKING_DIRECTORY /workspaces/cs225/release-f22/release-f22/lab_quacks/build)
add_test( [==[scramble 17]==] /workspaces/cs225/release-f22/release-f22/lab_quacks/build/test [==[scramble 17]==]  )
set_tests_properties( [==[scramble 17]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225/release-f22/release-f22/lab_quacks/build)
add_test( [==[scramble 9]==] /workspaces/cs225/release-f22/release-f22/lab_quacks/build/test [==[scramble 9]==]  )
set_tests_properties( [==[scramble 9]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225/release-f22/release-f22/lab_quacks/build)
set( test_TESTS sumDigits triangle sum isBalanced [==[scramble 17]==] [==[scramble 9]==])
