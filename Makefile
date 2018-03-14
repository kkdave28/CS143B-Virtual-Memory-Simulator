default:
	g++ main.cpp BitMap.cpp MainMem.cpp TLB.cpp VirtualMem.cpp -std=c++11 -ggdb -o main
checkop:
	python cs143b_virt_mem_output_checker.py 61699159.txt 61699159_tlb.txt
clean:
	rm -f main
	rm -f core.*
	rm -f vgcore.*
	rm -f 61699159.txt
	rm -f 61699159TLB.txt
	rm -f 61699159_tlb.txt
