; ModuleID = 'TestMod'
source_filename = "TestMod"

@0 = private unnamed_addr constant [13 x i8] c"Hello World!\00", align 1

declare i32 @puts(i8*)

define i32 @main() {
entry:
  %0 = call i32 @puts(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @0, i32 0, i32 0))
  ret i32 0
}
