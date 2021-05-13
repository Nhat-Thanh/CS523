# Khảo sát Btree bằng phần mềm SQLite
## Quá trình test.
- Trình tự thực hiện hành động: **INSERT** --> **UPDATE** --> **BETWEEN** --> **RANK** --> **DELETE**
- database dùng để kiểm thử có 1 table với ```500.000.000``` record, mỗi record chứa 1 sô, và giá trị thuộc đoạn ```[1,500.000.000]```.
- **INSERT, BETWEEN, DELETE** thực hiện với ```50.000.000``` record.
- **UPDATE, RANK** thực hiện với 5 triệu record.
## Cấu trúc chức năng các thành phần trong cây thư mục.	
- Thư mục **operating_script** chứa các file shell mà file **Btree.sh** gọi tới để thực thi các hành động tương ứng của sqlite.
	+ **insert.sh** thực hiện insert ```50.000.000``` record vào database.
	+ **delete.sh** xóa các số ```> 550.000.000``` trong database.
	+ **rank.sh** thực hiện rank ```5.000.000``` lần.
	+ **between.sh** thực hiện between ```50.000.000``` lần.
	+ **update.sh** update các giá trị theo công thức ```n = n + 50.000.000``` với n thuộc đoạn ```[500.000.001, 505.000.000]```.
- Thư mục ***sheet*** chứa các bảng tính thống kê kết quả của các hành động.
- Thư mục ***sql*** chứa các file sql được chứa trong các thư mục có tên tương ứng với các hành động.
- Thư mục **result** dùng để lưu kết quả vào các thư mục tương ứng sau khi chạy các hành động của sqlite. 
- **Makefile** dùng để build file .cpp và thực thi file CreateDatabase.sh.
- **create_sql_files.cpp** dùng để tạo ra các file sql được lưu trong các thư mục với tên và hành động tương ứng.
- **CreateDatabase.sh** dùng để tạo ra một database mẫu, database này được lưu vào file **database.db**.
- **measure_ram.sh** chứa các lệnh dùng để đo lượng Ram được sử dụng bởi sqlite khi thực thi và lưu kết quả vào file.
- **recovery.sh** dùng để khôi phục database lại trạng thái ban đầu.
- **Btree.sh** là file thực thi chính, nó chứa gọi các file shell khác để thực thi một hành động của sqlite, khi gọi file ta truyền đối số tương ứng với hành động sqlite thực hiện, các đối số có thể truyền ```insert, delete, update, rank, between, all```.
	+ vd: ```bash Btree.sh insert``` -> thực hiện insert các số trong file **insert_data.txt** vào database.
	+ Thực hiện toàn bộ hành động: ```bash Btree.sh all```.
