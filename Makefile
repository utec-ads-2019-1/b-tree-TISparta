test: FORCE
	g++ main.cpp mocker/mocker.cpp -o test

FORCE: ;

clean:
	rm test
