of = output\output
exe =  executable\Release\task

all: mkdir task1 task2 task3 task4 task5 task6 task7 task8 task9 task10 task11 task12 task13

mkdir:
	IF exist output ( echo output exists ) ELSE ( mkdir output && echo output created)
	
task1: mkdir
	$(exe)1.exe > $(of)1.txt

task2: mkdir
	$(exe)2.exe  > $(of)2.txt

task3: mkdir
	$(exe)3.exe  > $(of)3.txt

task4: mkdir
	$(exe)4.exe  > $(of)4.txt

task5: mkdir
	$(exe)5.exe  > $(of)5.txt

task6: mkdir
	$(exe)6.exe  > $(of)6.txt

task7: mkdir
	$(exe)7.exe  > $(of)7.txt

task8: mkdir
	$(exe)8.exe  > $(of)8.txt

task9: mkdir
	$(exe)9.exe  > $(of)9.txt

task10: mkdir
	$(exe)10.exe  > $(of)10.txt

task11: mkdir
	$(exe)11.exe  > $(of)11.txt

task12: mkdir
	$(exe)12.exe  > $(of)12.txt

task13: mkdir
	$(exe)13.exe  > $(of)13.txt