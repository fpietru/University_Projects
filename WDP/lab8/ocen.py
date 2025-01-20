import os
import sys
import time

curr_path = os.path.abspath(sys.argv[0])
curr_dir = os.path.dirname(curr_path)

if sys.argv[1] == "help":
	print("	1: nazwa folderu z testami")
	print("	2: nazwa programu")
	print("	3: nazwa testu .in/.out")
	print("	4: pierwszy numer do sprawdzenia")
	print("	5: ostatni numer do sprawdzenia")
	print("Ex: python3 ocen.py testy cuk testcuk 1 1000")
	exit()

test_dir = "/" + sys.argv[1]
program = "./" + sys.argv[2]
pattern = sys.argv[3]
start_idx = int(sys.argv[4])
end_idx = int(sys.argv[5])

in_ext = ".in" #sys.argv[4]
out_ext = ".out" #sys.argv[5]

in_dir = curr_dir + test_dir + "/in/"
out_dir = curr_dir + test_dir + "/out/"

count_files = 0
for f in os.listdir(in_dir):
	count_files += 1

count_ok = 0
count_wa = 0
start_time = time.time()

for i in range(start_idx, end_idx+1):
	os.system(f"{program} < {in_dir}{pattern}{i}{in_ext} > tmp_out")
	#print(f"{pattern}{i}{in_ext}")
	os.system(f"diff -w tmp_out {out_dir}{pattern}{i}{out_ext} > tmp_res")
	res_size = os.path.getsize(curr_dir+"/tmp_res")
	if (res_size == 0):
		print(f"\033[92mOK\033[0m [{pattern}{i}]")
		count_ok += 1
	else:
		print(f"\033[91mWA\033[0m [{pattern}{i}]")
		# os.system(f"python3 check.py {i}")
		count_wa += 1
		# break;

end_time = time.time()
exec_time = end_time - start_time

print("OK =", count_ok, " | WA =", count_wa, f" Czas wykonania: {exec_time:.5f} sekund")

os.remove(f"{curr_dir}/tmp_res")
os.remove(f"{curr_dir}/tmp_out")