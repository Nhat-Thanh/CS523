# Đồ án cuối kì

# Chủ đề: Log-Structured Merge-Tree

## Mục lục
* [Chuẩn bị cho quá trình thưc nghiệm](#chuẩn-bị-cho-quá-trình-thực-nghiệm)
* [Môi trường thử nghiệm](#môi-trường-thử-nghiệm)
* [Cấu trúc cây thư mục](#cấu-trúc-cay-thư-mục)
* [Thực nghiệm](#thực-nghiệm)

## Chuẩn bị cho quá trình thực nghiệm

### Môi trường thử nghiệm
- Hệ điều hành: Garuda Linux hoặc các GNU distro khác.
- Công cụ: shell, cmake, g++, du, pgrep, ps, wiredtiger.
- Yêu câu tối thiểu dung lượng trống trên đĩa cứng là 14GB.
- Nên thử nghiệm trên HDD để có kết quả chính xác hơn.
- Cách cài đặt wiredtiger: [tại đây](http://source.wiredtiger.com/1.4.2/install.html)

### Cấu trúc cây thư mục
- **`bin`**: Thư mục chứa các file chương trình thực thi. 
    + **`create_btree_table`**: Chương trình tạo table dùng BTree. 
    + **`create_lsm_table`**: Chương trình tạo table dùng LSM Tree. 
    + **`delete`**: Chương trình thực hiện thao tác xóa. 
    + **`insert`**: Chương trình thực hiện thao tác chèn. 
    + **`open`**: Chương trình thực hiện thao tác đóng mở database. 
    + **`print_db`**: Chương trình in toàn bộ record. 
    + **`search`**: Chương trình thực hiện thao tác tìm kiếm. 
    + **`update`**: Chương trình thực hiện thao tác cập nhật. 
    + **`check_and_fix`**: Sửa lỗi các file không có kết quả bằng cách chạy lại test đó. 
    + **`make_csv`**: Chương trình tạo file csv tự động. 

- **`btree_db`**: Thư mục này chứa 100 thư mục, mỗi thư mục con chứa 1 database có số record bằng với tên thư mục, các database liên tiếp sẽ lệch nhau 100 000 record. 
    + **`100000`**: Btree database có 100 000 record.
    + ...................
    + **`10000000`**: Btree database có 10 000 000 record.

- **`lsm_db`**: Chứa 100 thư mục, mỗi thư mục chứa 1 database có số record bằng với tên thư mục. 
    + **`100000`**: Btree database có 100 000 record.
    + ...................
    + **`10000000`**: Btree database có 10 000 000 record.

- **`result`**: Thư mục này chứa kết quả đo đạc của mọi thao tác trên cả Btree lẫn LSM tree. 
    + **`btree`** Chứa 6 thư mục tương ứng với kết quả của thao tác tương ứng trên các database sử dụng Btree, bên trong các thư mục con đều chứa 100 thư mục ứng với kết quả của database có số lượng record tương ứng.


      + **`delete`** Kết quả của thao tác delete.
        + **`100000`**: Btree database có 100 000 record.
        + ...................
        + **`10000000`**: Btree database có 10 000 000 record.

      + **`insert`** Kết quả của thao tác insert. 
        + Giống với **`delete`**

      + **`open`** Kết quả của thao tác open. 
        + Giống với **`delete`**

      + **`search`** Kết quả của thao tác search. 
        + Giống với **`delete`**

      + **`update`** Kết quả của thao tác update. 
        + Giống với **`delete`**

      + **`create_database`** Kết quả của thao tác create_database. 
        + Giống với **`delete`**
  
  + **`lsm`** Thư mục này chứa 6 thư mục tương ứng với kết quả của thao tác tương ứng trên các database sử dụng LSM tree, bên trong các thư mục con đều chứa 100 thư mục ứng với kết quả của database có số lượng record tương ứng. 
      + Giống với **`btree`**

- **`script`**: Thư mục này chứa các file shell, các file shell này gọi các chương trình trong thư mục **`bin`** và thao tác trên toàn bộ database:
    + **`compact.sh`**: merge LSM Tree. 
    + **`create_database.sh`**: Tạo database ứng với từng loại tree. 
    + **`delete.sh`**: Thực hiện xóa 100 000 record. 
    + **`init.sh`**: Tạo các các thư mục **`lsm_db`**, **`btree_db`**, **`bin`** và **`result`**. 
    + **`insert.sh`**: Thực hiện chèn 100 000 record. 
    + **`measure_swinfo.sh`**: Đo dung lượng RAM và đĩa cứng. 
    + **`open.sh`**: Thực hiện mở và đóng database. 
    + **`search.sh`**: Thực hiện tìm kiếm một key mong muốn 100 lần. 
    + **`update.sh`**: Thực hiện cập nhật 100 000 record. 

- **`sheet`**: Thư mục này chứa bảng kết quả của từng thao tác với từng loại tree:
    + **`btree_create_database.csv`**: tổng hợp kết quả của thao tác **create_database** trên các btree database.
    + **`btree_delete.csv`**: tổng hợp kết quả của thao tác **delete** trên các btree database.
    + **`btree_insert.csv`**: tổng hợp kết quả của thao tác **insert** trên các btree database.
    + **`btree_open.csv`**: tổng hợp kết quả của thao tác **open** trên các btree database.
    + **`btree_search.csv`**: tổng hợp kết quả của thao tác **search** trên các btree database.
    + **`btree_update.csv`**: tổng hợp kết quả của thao tác **update** trên các btree database.
    + **`lsm_create_database.csv`**: tổng hợp kết quả của thao tác **create_database** trên các lsm tree database.
    + **`lsm_delete.csv`**: tổng hợp kết quả của thao tác **delete** trên các lsm tree database.
    + **`lsm_insert.csv`**: tổng hợp kết quả của thao tác **insert** trên các lsm tree database.
    + **`lsm_open.csv`**: tổng hợp kết quả của thao tác **open** trên các lsm tree database.
    + **`lsm_search.csv`**: tổng hợp kết quả của thao tác **search** trên các lsm tree database.
    + **`lsm_update.csv`**: tổng hợp kết quả của thao tác **update** trên các lsm tree database.

- **`src`**: Thư mục chứa mã nguồn của các file chương trình thực thi trong thư mục **`bin`**:
    + **`check_and_fix.cpp`**
    + **`compact.cpp`**
    + **`create_btree_table.cpp`**
    + **`create_lsm_table.cpp`**
    + **`delete.cpp`**
    + **`insert.cpp`**
    + **`make_csv.cpp`**
    + **`open.cpp`**
    + **`print_db.cpp`**
    + **`search.cpp`**
    + **`update.cpp`**

- **`Makefile`** file tổng hợp các lệnh cần gọi để thực thi, giảm việc gõ lệnh và thực thi tự động, ta sẽ gọi mọi file thực thi khác thông qua file này.

**LƯU Ý**: nhũng con số trong phần mô tả trên chỉ là thực nghiệm đã được làm trước đó, các con số này có thể được tùy biến để tạo ra một thử nghiệm mới bằng cách thay đối giá trị của các tham số được truyền vào của **`Makefile`**.

## Thực nghiệm
- Trình tự thực hiện: create_database -> open -> insert -> search -> update -> delete.
- Sử dụng **`make`** để thực hiện tự động các các thao tác, Makefile có tổng cộng 7 tham số có thể truyền vào, các tham số này có thể tùy biến để phù hợp với các yêu cầu mong muốn:
	+ **`TREE_TYPE`**: đại diện cho loại của tree, tham số chỉ nhận giá trị "lsm" hoặc "btree", mặc định là "lsm".
	+ **`OP`**: viết tắt của "OPERATION", tham số chỉ nhận các giá trị trong tập `{create_database, open, insert, delete, update, seach}`, mặc định là "open".
	+ **`START`**: đại diện cho kích thước (số record) của database nhỏ nhất, mặc định là 100 000.
	+ **`END`**: đại diện cho kích thước (số record) của database lớn nhất, mặc định là 10 000 000.
	+ **`DB_SIZE`**: viết tắt của "DATABASE SIZE", đại diện cho kích thước (số record) của database, mặc định là 10 000 000.
	+ **`AMOUNT_FOR_OP`**: đại diện cho số lượng record mà một **`OP`** cần thao tác, mặc đinh là 100 000.
	+ **`STEP`**: đại diện số lượng record chênh lệch giữa 2 database liền nhau, mặc định là 100 000.

- Makefile có tổng cộng 16 nhãn, mỗi nhãn có thể được gọi để thực hiện một công việc, tất cả các nhãn đều cần được truyền tham số:
    - **`auto`**: Thực hiện mọi thử nghiệm một cách tự động
        + Các tham số cần truyền: **`START`**, **`END`**, **`STEP`**.
    - **`init`**: Tạo thư mục **`result`**, **`btree_db`**, **`lsm_db`**, **`bin`** và các thư mục con bên trong.
        + Các tham số cần truyền: **`START`**, **`END`**, **`STEP`**.
    - **`build_all_cpp`**: Build toàn bộ mã nguồn trong thư mục **`src`**.
        + Không cần truyền tham số.
    - **`build_cpp`**: Build file mã nguồn có tên giống với **`OP`**.
        + Tham số cần truyền: **`OP`**.
    - **`a_database`**: Tạo một database có kích thước **`DB_SIZE`**.
        + Các tham số cần truyền: **`TREE_TYPE`**, **`DB_SIZE`**.
    - **`databases`**: Tạo toàn bộ database của một loại tree.
        + Các tham số cần truyền: **`TREE_TYPE`**, **`START`**, **`END`**, **`STEP`**.
    - **`all_database`**: Tạo toàn bộ database của cả 2 tree.
        + Các tham số cần truyền: **`START`**, **`END`**, **`STEP`**.
    - **`test`**: Chạy thực nghiệm thao tác **`OP`** trên toàn bộ database loại **`TREE_TYPE`**.
        + Các tham số cần truyền: **`OP`**, **`TREE_TYPE`**, **`START`**, **`END`**, **`AMOUNT_FOR_OP`**, **`STEP`**.
    - **`test_btree`**: Chạy toàn bộ thực nghiêm với Btree.
        + Các tham số cần truyền: **`START`**, **`END`**, **`AMOUNT_FOR_OP`**, **`STEP`**.
    - **`test_lsm`**: Chạy toàn bộ thực nghiệm với LSM tree.
        + Các tham số cần truyền: **`START`**, **`END`**, **`AMOUNT_FOR_OP`**, **`STEP`**.
    - **`check_and_fix`**: Kiểm tra và sửa lại các test case lỗi.
        + Các tham số cần truyền: **`START`**, **`END`**, **`STEP`**.
    - **`fix`**: Sửa lại kết quả của thao tác **`OP`** trên database loại **`TREE_TYPE`** có **`DB_SIZE`** record.
        + Các tham số cần truyền: **`OP`**, **`TREE_TYPE`**, **`DB_SIZE`**, **`AMOUNT_FOR_OP`**.
    - **`fix_create_database`**: Sửa lại kết quả của thao tác **`create_database`** trên database loại **`TREE_TYPE`** có **`DB_SIZE`** record.
        + Các tham số cần truyền: **`OP`**, **`TREE_TYPE`**, **`DB_SIZE`**.
    - **`clean_all`**: Xóa **`btree_db`**, **`lsm_db`** và **`bin`**.
        + Không cần truyền tham số.
    - **`csv`**: Tạo các file csv từ kết quả của thực nghiệm.
        + Các tham số cần truyền: **`START`**, **`END`**, **`STEP`**.
    - **`compact`**: Thực hiện merge các LSM database.
        + Các tham số cần truyền: **`START`**, **`END`**, **`STEP`**.

- Cấu trúc của cây thư mục hiện tại dùng để chạy với các giá trị mặc đinh, nếu muốn chạy với các kích thước và giới hạn khác cần xóa 3 thư mục **`btree_db`**, **`lsm_db`**, **`result`** trước khi chạy.

- Các file shell cũng nhận vào các tham số:
    + **`create_database.sh`** `TREE_TYPE, START, END, STEP`.
    + **`compact.sh`** `START, END, STEP`.
    + **`init.sh`** `START, END, STEP`.
    + **`open.sh`** `TREE_TYPE, START, END, AMOUNT_FOR_OP, STEP`.
    + **`insert.sh`** `TREE_TYPE, START, END, AMOUNT_FOR_OP, STEP`.
    + **`search.sh`** `TREE_TYPE, START, END, AMOUNT_FOR_OP, STEP`.
    + **`update.sh`** `TREE_TYPE, START, END, AMOUNT_FOR_OP, STEP`.
    + **`delete.sh`** `TREE_TYPE, START, END, AMOUNT_FOR_OP, STEP`.

- Các file thực thi trong thư mục **`bin`** nhận vào các tham số, các tham số cần truyền được ghi trong các file mã nguồn, có thể truyền nhiều tham số hơn mức cần thiết nhưng cần phải đảm bảo thứ tự của các "tham số cần thiết".

- Có thể dụng lệnh **`make auto`** với các tham số để chạy toàn bộ thử nghiệm một cách tự động:
    + Lệnh dùng với cấu trúc thư mục hiện tại: **`make auto START=100000 END=10000000 STEP=100000 AMOUNT_FOR_OP=100000`**.
    + Có thể tùy biến **`START`**, **`END`**, **`STEP`** và **`AMOUNT_FOR_OP`** để phù hợp với mục đích, nếu tùy biến tham số thì cần xóa thư mục **`btee_db`**, **`lsm_db`**, **`result`** trước khi chạy **`make auto`**.

- Sau khi chạy xong toàn bộ thử nghiệm, cần chạy chương trình **`check_and_fix`** để sửa lại các test case bị lỗi do không đo được dung lượng RAM:
    + Lệnh để chạy: **`make check_and_fix START=100000 END=10000000 STEP=100000`**.
    + **`START`**, **`END`**, **`STEP`** phải giống với lúc chạy lệnh **`make auto`**.

- Sau khi kiểm tra và sửa lại các test case lỗi, chạy chương trình **`make_csv`** để tổng hợp toàn bộ kết quả và ghi ra file csv:
    + Lệnh để chạy: **`make csv START=100000 END=10000000 STEP=100000`**.
    + **`START`**, **`END`**, **`STEP`** phải giống với lúc chạy lệnh **`make auto`**.

- Chi tiết các bước thực hiện và kết quả thử nghiệm đều được ghi trong file báo cáo:
- Các kết quả được mô phỏng lại bằng colab:
