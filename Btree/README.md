# Khảo sát Btree bằng phần mềm SQLite
## Quá trình test.
- Trình tự thực hiện hành động: **OPEN** --> **SEARCH** --> **INSERT** --> **UPDATE** --> **BETWEEN** --> **RANK** --> **DELETE**
- Dùng make để tạo database mẫu: cú pháp ```make <nhãn> [SIZE=<một con số>]```
	+ `<nhãn>`:gồm `all`, ```SQL```, ```database```, ```auto```.
		+ ```all```: chạy 2 nhãn ```SQL```, ```database```.
		+ ```SQL```: build và run file ```create_sql_files.cpp```, xóa file thực thi của file ```create_sql_files.cpp``` sau khi build.
		+ ```database```: để chạy nhãn này cần truyền ```SIZE=<một con số>```, chạy file ```CreateDatabase``` với đối số ```SIZE```.
		+ ```auto```: thực hiện toàn bộ quá trình kiểm nghiệm.
	+ ```[SIZE=<một con số>]```: chỉ truyền khi chạy nhãn ```database```.
		+ ```SIZE=250000000```, ```SIZE=500000000```, ```SIZE=750000000```, ```SIZE=1000000000```, ```SIZE=1250000000```, ```SIZE=1500000000```, ```SIZE=1750000000```, ```SIZE=2000000000```.
- Chạy với 8 database có kích thước lần lượt là: 250 triệu, 500 triệu, 750 triệu, 1 tỷ, 1.25 tỷ, 1.5 tỷ, 1.75 tỷ, 2 tỷ.
- Các database dùng để kiểm thử có 1 table với số record thuộc ```{250000000, 500000000, 750000000, 1000000000, 1250000000, 1500000000, 1750000000, 2000.000.000}```, các database này được lưu vào file **database_"SIZE".db**, database này chỉ chứa duy nhất 1 table, table này chỉ chứa duy nhất 1 cột có kiểu INTEGER. mỗi record chứa 1 sô, và giá trị thuộc đoạn ```[1, kích thước database]```.
- **Chỉ tạo database mới** khi đã thực hiện xong toàn bộ các hành động **OPEN** --> **SEARCH** --> **INSERT** --> **UPDATE** --> **BETWEEN** --> **RANK** --> **DELETE**.
- Sau khi tạo database mới thì **phải xóa database cũ di** để đỡ tón dung lượng đĩa và để đo dung lượng ổ đĩa khi thực hiện các hành động trên database mới.
- **INSERT, UPDATE, DELETE** thực hiện với ```50.000.000``` record.
- **BETWEEN, RANK** thực hiện bằng cách đo thời gian của cùng 1 hành động 100 lần.
- **OPEN, SEARCH** thực hiện 1000 lần với cùng 1 hành động. 
## Các lệnh để thực hiện kiểm nghiệm khi test từng database.
1) ```make SQL```.
2) ```make database SIZE=250000000```
3) ```bash Btree all 250000000```
4) Xóa database cũ.
5) Quay lại và thực hiện bước 2 với ```SIZE``` thay đổi, ```SIZE``` và đối số truyền vào sau ```all``` của lệnh 3 phải giống nhau.
6) Thực hiện 5 bươc trên cho đến khi đủ 8 database :)).

## Lệnh rút gọn.
- Ta có thể gõ ```make auto``` để thực hiện toàn bộ quá trình kiểm nghiệm, việc còn lại là dạng háng, treo máy để chờ :)).
## Cấu trúc chức năng các thành phần trong cây thư mục.	
- Thư mục **operating_script** chứa các file shell mà file **Btree.sh** gọi tới để thực thi các hành động tương ứng của sqlite.
	+ **insert.sh** nhận 1 đối số ```SIZE (kích thước của database tương ứng)```, và thực hiện insert ```50.000.000``` record vào database đó.
	+ **delete.sh** nhận 1 đối số ```SIZE (kích thước của database tương ứng)```, và xóa các số ```> SIZE``` trong database đó.
	+ **rank.sh** nhận 1 đối số ```SIZE (kích thước của database tương ứng)```, và thực hiện rank ```100``` lần trong database đó.
	+ **between.sh** nhận 1 đối số ```SIZE (kích thước của database tương ứng)```, và thực hiện between ```100``` lần trong database đó.
	+ **update.sh** nhận 1 đối số ```SIZE (kích thước của database tương ứng)```, và update các giá trị theo công thức ```n = n + 50.000.000``` với ```n > SIZE```.
	+ **open.sh** nhận 1 đối số ```SIZE (kích thước của database tương ứng)```, thực hiện thao tác đóng mở database có kích thước ```SIZE``` 1000 lần.
	+ **search.sh** nhận 1 đối số ```SIZE (kích thước của database tương ứng)```, thực hiện tìm kiếm ```NUMBER = SIZE``` trong database có kích thước ```SIZE```.
- Thư mục ***sheet*** chứa các bảng tính thống kê kết quả của các hành động **OPEN, SEARCH, INSERT, UPDATE, BETWEEN, RANK, DELETE**.
- Thư mục ***sql*** chứa các file sql được chứa trong các thư mục có tên tương ứng với các hành động.
	+ Các thư mục có tên là các con số dùng để chứa các file ```.sql``` dùng để thao tác với database có ```SIZE``` tương ứng.
	+ Ví dụ thư mục `250000000` dùng để chứa các file sql dùng để thao tác với database có kích thước là `250000000` record.
- Thư mục **result** dùng để lưu kết quả vào các thư mục tương ứng sau khi chạy các hành động của sqlite.
 	+ Các thư mục tương ứng này được chứa trong các thư mục có tên là các con số tương ứng với ```SIZE``` của database được thao tác. 
 	+ Ví dụ thư mục `250000000` dùng để chứa các file kết quả sau khi thao tác với database có kích thước là `250000000` record.
- **Makefile** dùng để thực hiện toàn bộ quá trình thử nghiệm, build file .cpp và thực thi file CreateDatabase.sh.
- **create_sql_files.cpp** dùng để tạo ra các file ```.sql``` và lưu vào thư mục ```sql```.
- **CreateDatabase.sh** nhận 1 đối số ```SIZE (kích thước của database tương ứng)```, và dùng để tạo ra một database mẫu có số lượng record đúng bằng ```SIZE```.
- **measure_ram.sh** nhận 2 đối số ```SIZE (kích thước của database tương ứng)```, ```OPERATION (hành động thực thi)```, dùng để đo lượng Ram và dung lượng đĩa cứng được sử dụng bởi sqlite khi thực thi ```OPERATION``` trên database có ```SIZE``` record và lưu kết quả vào file.
- **recovery.sh** nhận 1 đối số ```SIZE (kích thước của database tương ứng)```, và dùng để khôi phục database có kích thước ban đầu là ```SIZE``` record.
- **Btree.sh** nhận 2 đối số ```SIZE (kích thước của database tương ứng)```, ```OPERATION (hành động thực thi)```, đây là file thực thi chính, nó thực thi ```OPERATION``` của sqlite với database có ```SIZE``` record, các đối số có thể truyền ```insert, delete, update, rank, between, open, search, all```.
	+ vd: ```bash Btree.sh insert 250000000``` -> thực hiện insert vào database có 250000000 record.
