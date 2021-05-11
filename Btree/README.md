# CS523
# Khảo sát Btree bằng phần mềm SQLite

- Trình tự thực hiện hành động: **INSERT** --> **UPDATE** --> **BETWEEN** --> **RANK** --> **DELETE**

- Thư mục **data** chứa các file text được tạo sau khi biên dịch và thực thi file **create_data_file.cpp**, những file này lưu các con số trên từng hàng, mỗi hàng là một con số, và các con số này không trùng nhau.
	+ **data.txt** chứa 10000000 số nguyên có giá trị trong khoảng ``[0, 10000000)``, được sắp xếp ngẫu nhiên, file **CreateDatabase.sh** sẽ lấy 1000000 số nguyên (1000000 dòng) đầu tiên để tạo database mẫu.

	+ **insert_data.txt** chứa các số nguyên là các dòng trong đoạn ``[1000001, 1000000 + n]`` của file **data.txt**, với n là tên thư mục chứa file này.

	+ **delete_data.txt** chứa các số nguyên là các dòng trong đoạn ```[1000001, 1000000 + 2n]``` của file **data.txt**, với n là tên thư mục chứa file này.

	+ **old_data_for_update_operation.txt** chứa nội dung giống với file **insert.txt**.
	+ **new_data_for_update_operation.txt** chứa nội dung giống với file **delete_data.txt**.
	+ **rank_data.txt** chứa n số nguyên có giá trị ngẫu nhiên trong đoạn ``[Min, Max]``, với ``Min``, ``Max`` lần lượt là số bé nhất và lớn nhất của dãy số nguyên của ``1000000 + 2n`` dòng đầu tiên trong file **data.txt**, với n là tên thư mục chứa file này.
	+ **between_data.txt** chứa 2n số nguyên, với số nguyên tại các dòng chẵn sẽ luôn lớn hơn số nguyên tại dòng ngay trước nó, các số nguyên có giá trị ngẫu nhiên trong đoạn ``[Min, Max]``, với ``Min``, ``Max`` lần lượt là số bé nhất và lớn nhất của dãy số nguyên của ``1000000 + 2n`` dòng đầu tiên trong file **data.txt**, với n là tên thư mục chứa file này.
	
- Thư mục **operating_script** chứa các file shell mà file **Btree.sh** gọi tới để thực thi các hành động tương ứng của sqlite.
	+ **insert.sh** lấy dữ liệu từ file **insert_data.txt** sau đó thưc hiện hành động chèn toàn bộ dữ liệu đó vào database.
	+ **delete.sh** lấy dữ liệu cần xóa từ file **delete_data.txt**, sau đó thưc hiện hành động xóa trong database dựa vào dữ liệu đó.
	+ **rank.sh** lấy dữ liệu từ **rank_data.txt**, sau đó thực hiện hành động rank trong database.
	+ **between.sh** lấy dữ liệu từ file **between_data.txt** sau đó thực hiện hành động between trong database.
	+ **update.sh** lấy dữ liệu từ 2 file là **old_data_for_update_operation.txt** và **new_data_for_update_operation.txt** để thực hiện hành động update.

- Thư mục **result** dùng để lưu kết quả vào các thư mục tương ứng sau khi chạy các hành động của sqlite. 
- **create_data_file.cpp** dùng để tạo ra các file text, những file text này chứa 1 số trên mỗi hàng và các con số này không trùng nhau.
- **CreateDatabase.sh** dùng để tạo ra một database mẫu, database này được lưu vào file **database.db**.
- **init.sh**, file này không nhất thiết phải chạy nếu đã có sẵn data file và database mẫu, nó chứa các lệnh dùng để biên dịch file **create_data_file.cpp**, gọi file **CreateDatabase.sh** để tạo database mẫu.
- **measure_ram.sh** chứa các lệnh dùng để đo lượng Ram được sử dụng bởi sqlite khi thực thi và lưu kết quả vào file.
- **database.db** là file database mẫu được tạo sau khi chạy file **CreateDatabase.sh**.
- **Bree.sh** là file thực thi chính, nó chứa gọi các file shell khác để thực thi một hành động của sqlite, khi gọi file ta truyền cho nó một chuỗi tương ứng với hành động mà minh muốn sqlite thực hiện.
	+ vd: ```bash Btree.sh insert``` -> thực hiện insert các số trong file **insert_data.txt** vào database.
	+ Có thể chạy lệnh này để thực hiện toàn bộ quá trình: ```bash Btree.sh insert && bash Btree.sh update && bash Btree.sh between && bash Btree.sh rank && bash Btree.sh delete```.
