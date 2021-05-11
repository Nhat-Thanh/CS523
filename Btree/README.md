# CS523
# Khảo sát Btree bằng phần mềm SQLite

Trình tự thực hiện hành động: INSERT -> UPDATE ->BETWEEN -> RANK ->DELETE

- Thư mục “data” chứa các file text được tạo sau khi biên dịch và thực thi file “create_data_file.cpp”, những file này lưu các con số trên từng hàng, mỗi hàng là một con số, và các con số này không trùng nhau.
	+ “data.txt” chứa 10000000 số nguyên có giá trị trong khoảng [0, 10000000), được sắp xếp ngẫu nhiên, file “CreateDatabase.sh” sẽ lấy 1000000 số nguyên (1000000 dòng) đầu tiên để tạo database mẫu.

	+ “insert_data.txt” chứa 1000 số nguyên, được trích từ dòng 1000001 đến dòng thứ 1001000 của file data.txt

	+ “delete_data.txt” chứa 1000 số nguyên được trích từ dòng 1001001 đến dòng 1002000 của file “data.txt”

	+ “old_data_for_update_operation.txt” chứa nội dung giống với file insert.txt
	+ “new_data_for_update_operation.txt” có nội dung giống với file delete_data.txt
	+ “rank_data.txt” chứa 1000 số nguyên có giá trị ngẫu nhiên trong đoạn [Min, Max], với Min, Max lần lượt là số bé nhất và lớn nhất của dãy số nguyên của 1002000 dòng đầu tiên trong file “data.txt”.
	+ “between_data.txt” chứa 2000 số nguyên, với các số nguyên tại dòng lẻ sẽ luôn lớn hơn số nguyên tại dòng ngay trước nó, các ố nguyên có giá trị ngẫu nhiên trong đoạn [Min, Max], với Min, Max lần lượt là số bé nhất và lớn nhất của dãy số nguyên của 1002000 dòng đầu tiên trong file “data.txt”.
	
- Thư mục “operating_script” chứa các file shell mà file “Btree.sh” gọi tới để thực thi các hanh động tương ứng của sqlite
	+ “insert.sh” lấy dữ liệu từ file “insert_data.txt” sau đó thưc hiện lệnh chèn toàn bộ vào database
	+ “delete.sh” lấy dữ liệu cần xóa từ file “delete_data.txt”, sau đó thưc hiện lệnh xóa trong database dựa vào dữ liệu đó
	+ “rank.sh” lấy dữ liệu từ “rank_data.txt”, sau đó thực hiện hành động rank trong database
	+ “between.sh” lấy dữ liệu từ file “between_data.txt” sau đó thực hiện lệnh between trong database 
	+ “update.sh” lấy dữ liệu từ 2 file là “old_data_for_update_operation.txt” và 
“new_data_for_update_operation.txt” để thực hiện hành động update.

- Thư mục result dùng để lưu kết quả vào các thư mục tương ứng sau khi chạy các hanh dộng của sqlite. 
- “create_data_file.cpp” dùng để tạo ra các file text, những file text này chứa 1 số trên mỗi hàng và các con số này không trùng nhau
- “CreateDatabase.sh” dùng để tạo ra một database mẫu, database này được lưu vào file “database.db”.
- “init.sh” chứa các lệnh dùng để biên dịch file “create_data_file.cpp”, gọi file “CreateDatabase.sh” để tạo database mẫu, file này không nhất thiết phải chạy nếu đã có sẵn data file và database mẫu.
- “measure_ram.sh” chứa các lệnh dùng để đo lượng Ram được sử dụng bởi sqlite thực thi và lưu kết quả vào file
- “database.db” là file database mẫu được tạo sau khi chạy file “CreateDatabase.sh”
- “Bree.sh” là file thực thi chinh, nó chứa các lệnh cần thiết đồng thời gọi các file shell khác để thực thi một hanh động của sqlite, khi gọi file ta truyền cho nó một chuỗi tương ứng với hanh động mà minh muốn sqlite thực hiện.
	+ vd: bash Btree.sh insert 
	+ // thực hiện insert các số trong file insert_data.txt vào database
