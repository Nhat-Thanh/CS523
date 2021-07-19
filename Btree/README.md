# This is going to be updated later.
# Khảo sát Btree bằng phần mềm SQLite

## Yêu cầu
Tìm hiểu và khảo sát hoạt động của B-Tree được cài đặt qua chương trình tham khảo SQLite

Sinh viên tạo một database chỉ có 1 table duy nhất, trong table chỉ có 1 column duy nhất kiểu số nguyên và được index. Kiểm tra cách sqlite cài đặt b-tree bằng cách đo đạc thời gian, dung lượng ram và dung lượng đĩa cứng sử dụng cho các thao tác sau:

- Thời gian open một B-Tree có n phần tử

- Thời gian tìm một phần tử trong B-Tree có n phần tử

- Thời gian xóa một phần tử trong B-Tree có n phần tử

- Thời gian thay đổi giá trị của một phần tử. Trả lời câu hỏi liệu thay đổi giá trị có khác gì với việc xóa đi rồi thêm mới?

- Tìm Rank của một phần tử

- Tìm các phần tử có giá trị nằm trong khoảng cho nào đó

Lưu ý là các thao tác trên có thể được thực hiện rất nhanh. Nên để đó thời gian của một thao tác, đôi khi ta cần lặp đi lặp lại thao tác đó nhiều lân và đo thời gian tổng.

Báo cáo chuẩn bị cho seminar nén lại bằng file .zip và nộp tại đây, nội dung cần có:

Các đoạn script, và các mã nguồn chương trình đã sử dụng khi thử nghiệm: file mã nguồn hoặc/và file colab notebook

File bảng tính thống kê số liệu

File báo cáo mô tả quá trình nghiệm, phân tích số liệu và kết luận, nhận xét

## Quá trình test.
- Trình tự thực hiện hành động: **OPEN** --> **SEARCH** --> **INSERT** --> **UPDATE** --> **BETWEEN** --> **RANK** --> **DELETE**
- Dùng make để tạo database mẫu: cú pháp `make <nhãn> [SIZE=<một con số>]`
	+ `<nhãn>`:gồm `all`, `SQL`, `database`, `auto`.
		+ `all`: chạy 2 nhãn `SQL`, `database`.
		+ `SQL`: build và run file `create_sql_files.cpp`, xóa file thực thi của file `create_sql_files.cpp` sau khi build.
		+ `database`: để chạy nhãn này cần truyền `SIZE=<một con số>`, chạy file `CreateDatabase` với đối số `SIZE`.
		+ `auto`: thực hiện toàn bộ quá trình kiểm nghiệm.
	+ `[SIZE=<một con số>]`: chỉ truyền khi chạy nhãn `database`.
		+ `SIZE=250000000`, `SIZE=500000000`, `SIZE=750000000`, `SIZE=1000000000`, `SIZE=1250000000`, `SIZE=1500000000`, `SIZE=1750000000`, `SIZE=2000000000`.
- Chạy với 8 database có kích thước lần lượt là: 250 triệu, 500 triệu, 750 triệu, 1 tỷ, 1.25 tỷ, 1.5 tỷ, 1.75 tỷ, 2 tỷ.
- Các database dùng để kiểm thử có kích thước thuộc `{250000000, 500000000, 750000000, 1000000000, 1250000000, 1500000000, 1750000000, 2000000000}`, các database này được lưu vào file **database_"SIZE".db**, database này chỉ chứa duy nhất `1 table tên Btree`, table này chỉ chứa duy nhất 1 cột có kiểu INTEGER. mỗi record chứa 1 sô, và giá trị thuộc đoạn `[1, kích thước database]`.
- **Chỉ tạo database mới** khi đã thực hiện xong toàn bộ các hành động **OPEN** --> **SEARCH** --> **INSERT** --> **UPDATE** --> **BETWEEN** --> **RANK** --> **DELETE**.
- Sau khi tạo database mới thì **phải xóa database cũ di** để đỡ tón dung lượng đĩa và để đo dung lượng ổ đĩa khi thực hiện các hành động trên database mới.
- **INSERT, UPDATE, DELETE** thực hiện với `50.000.000` record.
- **BETWEEN, RANK** thực hiện bằng cách đo thời gian của cùng 1 hành động 100 lần.
- **OPEN, SEARCH** thực hiện 1000 lần với cùng 1 hành động. 
## Các lệnh để thực hiện kiểm nghiệm khi test từng database.
1) `make SQL`.
2) `make database SIZE=250000000`
3) `bash Btree all 250000000`
4) Xóa database cũ.
5) Quay lại và thực hiện bước 2 với `SIZE` thay đổi, `SIZE` và đối số truyền vào sau `all` của lệnh 3 phải giống nhau.
6) Thực hiện 5 bươc trên cho đến khi đủ 8 database :)).

## Lệnh rút gọn.
- Ta có thể gõ `make auto` để thực hiện toàn bộ quá trình kiểm nghiệm, việc còn lại là dạng háng, treo máy để chờ :)).
## Cấu trúc chức năng các thành phần trong cây thư mục.	
- Thư mục **operating_script** chứa các file shell mà file **Btree.sh** gọi tới để thực thi các hành động tương ứng của sqlite.
	+ **insert.sh** nhận 1 đối số `SIZE (kích thước của database tương ứng)`, và thực hiện insert `50000000` record vào database đó.
	+ **delete.sh** nhận 1 đối số `SIZE (kích thước của database tương ứng)`, và xóa các số `> SIZE` trong database đó.
	+ **rank.sh** nhận 1 đối số `SIZE (kích thước của database tương ứng)`, và thực hiện rank `100` lần trong database đó.
	+ **between.sh** nhận 1 đối số `SIZE (kích thước của database tương ứng)`, và thực hiện between `100` lần trong database đó.
	+ **update.sh** nhận 1 đối số `SIZE (kích thước của database tương ứng)`, và update các giá trị theo công thức `n = n + 50000000` với `n > SIZE`.
	+ **open.sh** nhận 1 đối số `SIZE (kích thước của database tương ứng)`, thực hiện thao tác đóng mở database có kích thước `SIZE` 1000 lần.
	+ **search.sh** nhận 1 đối số `SIZE (kích thước của database tương ứng)`, thực hiện tìm kiếm `NUMBER = SIZE` trong database có kích thước `SIZE`.
- Thư mục **sheet** chứa các bảng tính thống kê kết quả của các hành động **OPEN, SEARCH, INSERT, UPDATE, BETWEEN, RANK, DELETE**.
- Thư mục **sql** chứa các file sql được chứa trong các thư mục có tên tương ứng với các hành động.
	+ Các thư mục có tên là các con số dùng để chứa các file `.sql` dùng để thao tác với database có `SIZE` tương ứng.
	+ Ví dụ thư mục `250000000` dùng để chứa các file sql dùng để thao tác với database có kích thước là `250000000` record.
- Thư mục **result** dùng để lưu kết quả vào các thư mục tương ứng sau khi chạy các hành động của sqlite.
 	+ Các thư mục tương ứng này được chứa trong các thư mục có tên là các con số tương ứng với `SIZE` của database được thao tác. 
 	+ Ví dụ thư mục `250000000` dùng để chứa các file kết quả sau khi thao tác với database có kích thước là `250000000` record.
- **Makefile** dùng để thực hiện toàn bộ quá trình thử nghiệm, build file .cpp và thực thi file CreateDatabase.sh.
- **create_sql_files.cpp** dùng để tạo ra các file `.sql` và lưu vào thư mục `sql`.
- **CreateDatabase.sh** nhận 1 đối số `SIZE (kích thước của database tương ứng)`, và dùng để tạo ra một database mẫu có số lượng record đúng bằng `SIZE`.
- **measure_ram.sh** nhận 2 đối số `SIZE (kích thước của database tương ứng)`, `OPERATION (hành động thực thi)`, dùng để đo lượng Ram và dung lượng đĩa cứng được sử dụng bởi sqlite khi thực thi `OPERATION` trên database có `SIZE` record và lưu kết quả vào file.
- **recovery.sh** nhận 1 đối số `SIZE (kích thước của database tương ứng)`, và dùng để khôi phục database có kích thước ban đầu là `SIZE` record.
- **Btree.sh** nhận 2 đối số `SIZE (kích thước của database tương ứng)`, `OPERATION (hành động thực thi)`, đây là file thực thi chính, nó thực thi `OPERATION` của sqlite với database có `SIZE` record, các đối số có thể truyền `insert, delete, update, rank, between, open, search, all`.
	+ vd: `bash Btree.sh insert 250000000` -> thực hiện insert vào database có 250000000 record.

- Kết quả được mô phỏng bằng colab: [Tại đây](https://colab.research.google.com/drive/15-eo0HgmPYuE73_BmRjd_5HZxYTiKxf-?usp=sharing)
