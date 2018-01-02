#define a multiline variable  
define target   
    echo $@  
    echo $@  
endef  
  
name := a b c d

files := $(foreach n, $(name), $(n).o)
strings := $(subst ee,EE, free on the street)
#define the target which is the first target, so default target  
all:  
	$(call target,all)  
	@echo ${files}
	$(if , @echo "Hello world", @echo "Say Good bye")
	@echo $(1) $(2)
	@echo ${strings}
  
#define the second target, we must explicitly make it  
clean:  
	$(call target,clean)      
  
#declare that all and clean are phony targets  
.PHONY: all clean  
