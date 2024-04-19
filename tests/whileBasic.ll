; ModuleID = 'TestMod'
source_filename = "TestMod"

@0 = private unnamed_addr constant [20 x i8] c"Loop Iteration: %d\0A\00", align 1

declare i32 @printf(...)

define i32 @main() {
entry:
  %i = alloca i32, align 4
  store i32 0, i32* %i, align 4
  br label %whileLoop

whileLoop:                                        ; preds = %whileLoopBody, %entry
  %0 = load i32, i32* %i, align 4
  %cmpResult = icmp slt i32 %0, 8
  br i1 %cmpResult, label %whileLoopBody, label %whileLoopEnd

whileLoopBody:                                    ; preds = %whileLoop
  %1 = load i32, i32* %i, align 4
  %2 = call i32 (...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @0, i32 0, i32 0), i32 %1)
  %3 = load i32, i32* %i, align 4
  %4 = add i32 %3, 1
  store i32 %4, i32* %i, align 4
  br label %whileLoop

whileLoopEnd:                                     ; preds = %whileLoop
  ret i32 0
}
