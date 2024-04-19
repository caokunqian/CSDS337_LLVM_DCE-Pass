; ModuleID = 'TestMod'
source_filename = "TestMod"

@0 = private unnamed_addr constant [4 x i8] c"%f\0A\00", align 1

declare i32 @printf(...)

define double @add(i32 %a, double %b) {
entry:
  %a1 = alloca i32, align 4
  %b2 = alloca double, align 8
  store i32 %a, i32* %a1, align 4
  store double %b, double* %b2, align 8
  %0 = load i32, i32* %a1, align 4
  %1 = sitofp i32 %0 to double
  %2 = load double, double* %b2, align 8
  %3 = fadd double %1, %2
  %4 = load i32, i32* %a1, align 4
  %5 = sitofp i32 %4 to double
  %6 = load double, double* %b2, align 8
  %7 = fadd double %5, %6
  ret double %7
}

define i32 @main() {
entry:
  %0 = call double @add(i32 3, double 7.000000e+00)
  %1 = call i32 (...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0), double %0)
  ret i32 0
}
