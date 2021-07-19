# External Sort

## Mục lục
* [Yêu cầu](#yêu-cầu)
* [Môi trường](#môi-trường)
* [Cấu trúc cây thư mục](#cấu-trúc-cây-thư-mục)
* [Thực nghiệm](#thực-nghiệm)

## Yêu cầu
Chạy thử và phân tích độ phức tạp của bài toán External sort.

Chương trình tham khảo: GNU Sort

1. Viết chương trình phát sinh input cho bài toán. Yêu cầu là file input khi nạp vào mảng sẽ có kích lớn hơn kích thước RAM trong máy. (4 tỷ số nguyên, mỗi số giá trị ngẫu nhiên trong khoảng 2 tỷ)

2. Sắp xếp file trên bằng chương trình tham khảo bất kỳ và ghi nhận các số liệu về: "Thời gian thực thi", "Bộ nhớ mà chương trình sử dụng"

3. Ghi nhận thời gian thực thi của GNU Sort - với bộ nhớ đệm (buffer) được set ở các kích thước khác nhau.

4. Ước tính độ phức tạp của GNU Sort, bằng cách chạy nhiều lần với kích thước input tăng dần.

5. GNU Sort (hay một chương trình tham khảo khác) có thể chạy song song không, thời gian chạy thay đổi như thế nào theo số lượng CPU  core mà chương trình sử dụng?

Nội dung cần nộp lại TRƯỚC KHI SEMINAR bao gồm:

Các đoạn script, và các mã nguồn chương trình đã sử dụng khi thử nghiệm: file mã nguồn hoặc/và file colab notebook

File bảng tính thống kê số liệu

File báo cáo mô tả quá trình nghiệm, phân tích số liệu và kết luận, nhận xét

## Môi trường
- OS: ubuntu 20.04
- Tools: bash, cmake, g++, pgrep, ps, sort.
- Dung lượng còn trống của phân vùng chứa OS phải trống trên 40GB, nếu không đủ có thể sử dụng lệnh **`ln`** để link thư mục **`/tmp`** sang ổ đĩa khác. Phải đảm bảo yếu tố này vì **`sort`** sinh ra file tạm và lưu chúng trong **`/tmp`**.

## Cấu trúc cây thư mục
- **`bin`**: chứa file thực thi
	- **`make_csv`**: tạo file csv tự động.
	- **`make_input_files`**: tạo các input file cho sort
- **`input`**: chứa các file input cho sort
- **`output`**: chứa file output.txt, file này chỉ dùng để chứa kết quả của mỗi lần sort
- **`result`**: chứa các file kết quả
	- **`complexity`**: chứa kết quả sort của các file input với kích thước tăng dần.
		- **`1_trieu`**: chứa kết quả của file input có 1 triệu số nguyên
		- .............
		- **`50_trieu`**: chứa kết quả của file input có 50 triệu số nguyên.
		- **`4000_trieu`**: chứa kết quả của file input có 4 tỉ số nguyên.

	- **`buffer`**: chứa kết quả sort khi thay đổi dung lượng buffer.
		- **`50M`**: chứa kết quả của file input 50 triệu với buffer 50MB
		- .............
		- **`1000M`**: chứa kết quả của file input 50 triệu với buffer 1000MB

	- **`parallel`**: chứa kết quả của file input với lượng CPU core khác nhau
		- **`1`**: chứa kết quả của file input 50 triệu với lượng CPU core sử dụng là 1 
		- .............
		- **`8`**: chứa kết quả của file input 50 triệu với lượng CPU core sử dụng là 8

- **`script`**: chứa các file shell
	- **`4000.sh`**: sort file 4 tỉ số nguyên.
	- **`init`**: Tạo thư mục **`bin`**, **`reult`** và các thư mục con bên trong.
	- **`measure_buffer.sh`**: chạy test 50 triệu với buffer tăng dần.
	- **`measure_complexity.sh`**: chạy toàn bộ test (trừ 4 tỉ) và đo thời gian.
	- **`measure_parallel.sh`**: chạy test 50 triệu với lượng CPU core tăng dần.
	- **`measure_ram.sh`**: đo dung lượng ram trong lúc chạy.
	- **`sort.sh`**: thực hiện sort với các đối số được truyền vào.
- **`sheet`**: chứa các bảng tính.
	- **`complexity.csv`**: chứa kết quả cho việc đo độ phức tạp
	- **`buffer.csv`**: chứa bảng tính đo dung lượng buffer.
	- **`parallel.csv`**: chứa kết quả khi chạy với lượng CPU core khác nhau.
- **`src`**: chứa mã nguồn của các file thực thi trong **`bin`**
	- **`make_csv.cpp`**
	- **`make_input_files.cpp`**
- **`Makefile`**: gọi file này để thực thi.

- File **sort.sh** có nhiệm vụ sắp xếp file input và đồng thời chạy các lệnh trong file **measure_ram.sh** để đo các thông số cần thiết trong lúc sắp xếp, nó nhận các đối số là **SIZE**, **CORE_NUMBER**, **BUFFER**, **TEST_MODE**.
	+ **SIZE**: là kích thước ứng với file input, vd: **SIZE** = 10 -> nhận file có input là 10 triệu số nguyên.
	+ **CORE_NUMBER**: là số nhân CPU muốn dùng để sắp xếp file input.
	+ **BUFFER**: là dung lượng buffer muốn dùng để sắp xếp file input.
	+ **TEST_MODE**: dùng để xác định nội dung mình muốn kiểm thử và lưu file kết quả vào các đường dẫn khác nhau, có 3 giá trị có thể truyền là **complexity** (test độ phức tạp), **buffer** (test buffer tăng dần), **parallel** (test cpu core tăng dần)
	
- File **measure_ram.sh** dùng để đo các thông số của phần cứng khi thực thi lệnh **sort** (không phải **sort.sh**), nó nhận các đối số là **SIZE**, **CORE_NUMBER**, **BUFFER**, **TEST_MODE**
	+ **SIZE**: là kích thước ứng với file input, vd: **SIZE** = 50 -> nhận file có input là 5 triệu số nguyên.
	+ **CORE_NUMBER**: là số nhân CPU muốn dùng để sắp xếp file input.
	+ **BUFFER**: là dung lượng buffer muốn dùng để sắp xếp file input.
	+ **TEST_MODE**: dùng để xác định nội dung mình muốn kiểm thử và lưu file kết quả vào các đường dẫn khác nhau, có 3 giá trị có thể truyền là **complexity** (test độ phức tạp với input tăng dần), **buffer** (test buffer tăng dần), **parallel** (test với số nhân CPU tăng dần)
	
Các file trên cũng chỉ có thể sắp xếp và đo thông số cho 1 file input duy nhất, em viết thêm các file là **measure_buffer.sh**, **measure_complexity.sh**, **measure_parallel.sh**.
  + **measure_complexity.sh**: file này dùng để đo độ phức tạp bằng cách gọi file **sort.sh** nhiều lần, file này không nhận đối số.
  + **measure_buffer.sh**: file này dùng để đo thời gian thực thi của file input có 50 triệu số khi chạy lệnh sort với các buffer khác nhau, file này không nhận đối số.
  + **meausure_parallel.sh**: file này dùng để đo thời gian thực thi của file input có 50 triệu số nguyên khi chạy lệnh sort với buffer cố định và số nhân CPU tăng dần sau các lần test, file này không nhận đối số.

## Thực nghiệm
- Câu lệnh để thực thi: **`make auto`**
- Kết quả được mô phỏng bằng colab: [Tại đây](https://colab.research.google.com/drive/1PJivYMhaCQ7VUYrsVWnMm8hhyfB1rk6N?usp=sharing)
