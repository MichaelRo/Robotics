################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Helper.cpp \
../Manager.cpp \
../Map.cpp \
../Robot.cpp \
../main.cpp 

OBJS += \
./Helper.o \
./Manager.o \
./Map.o \
./Robot.o \
./main.o 

CPP_DEPS += \
./Helper.d \
./Manager.d \
./Map.d \
./Robot.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


