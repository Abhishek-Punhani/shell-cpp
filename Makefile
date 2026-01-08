.PHONY: all build clean run

all: build

build:
	mkdir -p build
	cd build && cmake .. && make -j$(nproc)

clean:
	rm -rf build

run: build
	./build/shell

docker-up:
	docker compose up --build -d
	docker run -it shell-cpp
docker-down:	docker compose down	--remove-orphans --volumes