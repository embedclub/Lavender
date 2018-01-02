#Makefile 用于学习目标和依赖的执行关系



.PHONY:target1

all1:target1
	@echo "all1_target1_.PHONY_command_all1"
target1:
	@echo "all1_target1_.PHONY_command_target1"
all2:target2
	@echo "all2_target2_command_all2"
target2:
	@echo "all2_target2_command_target2"
all3:target3 all2 all1
	@echo "all3_target3_force_command_all3"
target3:
	make  all4
all4:target4
	@echo "all4_target4_::_command_all4"
target4::
	@echo "all4_target4_::_command_target4"

all5: target5
	@echo "all5_target4_::_command_all5"
target5: FORCE
	@echo "Force is not set value"

.PHONY: help FORCE
