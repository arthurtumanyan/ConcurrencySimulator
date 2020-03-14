Yet another solution for UVA-210 problem

Build instructions:

In any linux environment execute the following commands:

git clone https://github.com/arthurtumanyan/ConcurrencySimulator.git
cd ConcurrencySimulator
make

./cs -c 1 -f input.txt -d

Arguments:

	-c|--count -- simulations count
	-f|--file  -- input file tor read statements from
	-d		   -- enable debug mode (print detailed information)
	
	Program tested in Fedora Linux 30 environment
