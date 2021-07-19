# External Sort
# This is going to be updated later.

Để tạo sự tiện lợi cho quá trình thử nghiệm, thay vì phải gõ lai từng lệnh vào terminal dài dòng, em viết 2 file là ***sort.sh*** và ***measure_ram.sh***.
- File ***sort.sh*** có nhiệm vụ sắp xếp file input và đồng thời chạy các lệnh trong file ***measure_ram.sh*** để đo các thông số cần thiết trong lúc sắp xếp, nó nhận các đối số là ***INDEX***, ***CORE_NUMBER***, ***BUFFER***, ***TEST_CONTENT***.
	+ ***INDEX***: là kích thước ứng với file input, vd: ***INDEX*** = 1000 -> nhận file có input là 1000 triệu (1 tỷ) số nguyên.
	+ ***CORE_NUMBER***: là số nhân CPU muốn dùng để sắp xếp file input.
	+ ***BUFFER***: là dung lượng buffer muốn dùng để sắp xếp file input.
	+ ***TEST_CONTENT***: dùng để xác định nội dung mình muốn kiểm thử và lưu file kết quả vào các đường dẫn khác nhau, có 3 giá trị có thể truyền là ***complexity*** (test độ phức tạp), ***buffer*** (test buffer tăng dần), ***parallel*** (test cpu core tăng dần)
	
- File ***measure_ram.sh*** dùng để đo các thông số của phần cứng khi thực thi lệnh ***sort*** (không phải ***sort.sh***), nó nhận các đối số là ***INDEX***, ***CORE_NUMBER***, ***BUFFER***, ***TEST_CONTENT***
	+ ***INDEX***: là kích thước ứng với file input, vd: ***INDEX*** = 500 -> nhận file có input là 500 triệu số nguyên.
	+ ***CORE_NUMBER***: là số nhân CPU muốn dùng để sắp xếp file input.
	+ ***BUFFER***: là dung lượng buffer muốn dùng để sắp xếp file input.
	+ ***TEST_CONTENT***: dùng để xác định nội dung mình muốn kiểm thử và lưu file kết quả vào các đường dẫn khác nhau, có 3 giá trị có thể truyền là ***complexity*** (test độ phức tạp với input tăng dần), ***buffer*** (test buffer tăng dần), ***parallel*** (test với số nhân CPU tăng dần)
	
Các file trên cũng chỉ có thể sắp xếp và đo thông số cho 1 file input duy nhất, em viết thêm các file là ***measure_buffer.sh***, ***measure_complexity.sh***, ***measure_parallel.sh***.
  + ***measure_complexity.sh***: file này dùng để đo độ phức tạp bằng cách gọi file ***sort.sh*** nhiều lần, file này không nhận đối số.
  + ***measure_buffer.sh***: file này dùng để đo thời gian thực thi của file input có 500 triệu số khi chạy lệnh sort với các buffer khác nhau, file này không nhận đối số.
  + ***meausure_parallel.sh***: file này dùng để đo thời gian thực thi của file input có 500 triệu số nguyên khi chạy lệnh sort với buffer cố định và số nhân CPU tăng dần sau các lần test, file này không nhận đối số.
