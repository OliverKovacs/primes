c:
	clang main.c -o main -O3
	./main

cpp:
	clang++ main.cpp -o main -O3
	./main

julia:
	julia main.jl

node:
	node main.js

deno:
	deno run main.js

ts_node:
	tsc main.ts --outFile main.ts.js --lib dom,esnext
	node main.ts.js

ts_deno:
	tsc main.ts --outFile main.ts.js --lib dom,esnext
	deno run main.ts.js

python:
	python3 main.py

rust:
	rustc main.rs -o main -C opt-level=3 -C target-cpu=native
	./main
