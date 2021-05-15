# Khảo sát Btree bằng phần mềm SQLite
## Quá trình test.
- Trình tự thực hiện hành động: **INSERT** --> **UPDATE** --> **BETWEEN** --> **RANK** --> **DELETE**
- Dùng make để tạo database mẫu: cú pháp ```make <nhãn> [SIZE=<một con số>]```
	+ ```<nhãn>```:gồm ```all```, ```SQL```, ```database```, ```clean```.
		+ ```all```: chạy 2 nhãn ```SQL```, ```database```.
		+ ```SQL```: build và run file ```create_sql_files.cpp```.
		+ ```database```: để chạy nhãn này cần truyền ```SIZE=<một con số>```, chạy file ```CreateDatabase``` với đối số ```SIZE```.
		+ ```clean```: xóa file thực thi của file ```create_sql_files.cpp``` sau khi build.
	+ ```[SIZE=<một con số>]```: chỉ truyền khi chạy nhãn ```database```.
		+ ```SIZE=250000000```, ```SIZE=500000000```, ```SIZE=750000000```, ```SIZE=1000000000```, ```SIZE=1250000000```, ```SIZE=1500000000```, ```SIZE=1750000000```, ```SIZE=2000000000```.
- Chạy với 8 database có kích thước lần lượt là: 250 triệu, 500 triệu, 750 triệu, 1 tỷ, 1.25 tỷ, 1.5 tỷ, 1.75 tỷ, 2 tỷ.
- **Chỉ tạo database mới** khi đã thực hiện xong toàn bộ các hành động **INSERT** --> **UPDATE** --> **BETWEEN** --> **RANK** --> **DELETE**.
- Sau khi tạo database mới thì **phải xóa database cũ di** để đo dung lượng ổ đĩa khi thực hiện các hành động trên database mới.
- Các database dùng để kiểm thử có 1 table với số record thuộc ```{250000000, 500000000, 750000000, 1000000000, 1250000000, 1500000000, 1750000000, 2000.000.000}```, mỗi record chứa 1 sô, và giá trị thuộc đoạn ```[1, kích thước database]```.
- **INSERT, UPDATE, DELETE** thực hiện với ```50.000.000``` record.
- **BETWEEN, RANK** thực hiện bằng cách đo thời gian của cùng 1 hành động 100 lần, sau đó trừ đi thời gian count.
## Các lệnh để thực hiện kiểm nghiệm.
1) ```make SQL```.
2) ```make database SIZE=250000000```
3) ```bash Btree all 250000000```
4) Xóa database cũ.
5) Quay lại và thực hiện bước 2 với ```SIZE``` thay đổi, ```SIZE``` và đối số truyền vào sau ```all``` của lệnh 3 phải giống nhau.
6) Thực hiện 5 bươc trên cho đến khi đủ 8 database :)).
## Cấu trúc chức năng các thành phần trong cây thư mục.	
- Thư mục **operating_script** chứa các file shell mà file **Btree.sh** gọi tới để thực thi các hành động tương ứng của sqlite.
	+ **insert.sh** nhận 1 đối số ```SIZE (kích thước của database tương ứng)```, và thực hiện insert ```50.000.000``` record vào database đó.
	+ **delete.sh** nhận 1 đối số ```SIZE (kích thước của database tương ứng)```, và xóa các số ```> SIZE + 50.000.000``` trong database đó.
	+ **rank.sh** nhận 1 đối số ```SIZE (kích thước của database tương ứng)```, và thực hiện rank ```500.000``` lần trong database đó.
	+ **between.sh** nhận 1 đối số ```SIZE (kích thước của database tương ứng)```, và thực hiện between ```500.000``` lần trong database đó.
	+ **update.sh** nhận 1 đối số ```SIZE (kích thước của database tương ứng)```, và update các giá trị theo công thức ```n = n + 50.000.000``` với ```n > SIZE```.
- Thư mục ***sheet*** chứa các bảng tính thống kê kết quả của các hành động.
- Thư mục ***sql*** chứa các file sql được chứa trong các thư mục có tên tương ứng với các hành động.
	+ Các thư mục có tên là các con số dùng để chứa các file ```.sql``` dùng để thao tác với database có ```SIZE``` tương ứng
- Thư mục **result** dùng để lưu kết quả vào các thư mục tương ứng sau khi chạy các hành động của sqlite.
 	+ Các thư mục tương ứng này được chứa trong các thư mục có tên là các con số tương ứng với ```SIZE``` của database được thao tác. 
- **Makefile** dùng để build file .cpp và thực thi file CreateDatabase.sh.
- **create_sql_files.cpp** dùng để tạo ra các file ```.sql``` được lưu thư mục ```sql```.
- **CreateDatabase.sh** nhận 1 đối số ```SIZE (kích thước của database tương ứng)```, và dùng để tạo ra một database mẫu có số lượng record đúng bằng ```SIZE```, database này được lưu vào file **database_"SIZE".db**.
- **measure_ram.sh** nhận 2 đối số ```SIZE (kích thước của database tương ứng)```, ```OPERATION (hành động thực thi)```, dùng để đo lượng Ram và đĩa cứng được sử dụng bởi sqlite khi thực thi ```OPERATION``` trên database có ```SIZE``` record và lưu kết quả vào file.
- **recovery.sh** nhận 1 đối số ```SIZE (kích thước của database tương ứng)```, và dùng để khôi phục database có kích thước ban đầu là ```SIZE``` record.
- **Btree.sh** nhận 2 đối số ```SIZE (kích thước của database tương ứng)```, ```OPERATION (hành động thực thi)```, đây là file thực thi chính, nó thực thi ```OPERATION``` của sqlite với database có ```SIZE``` record, các đối số có thể truyền ```insert, delete, update, rank, between, all```.
	+ vd: ```bash Btree.sh insert 250000000``` -> thực hiện insert vào database có 250000000 record.
