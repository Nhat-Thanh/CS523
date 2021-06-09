# Khảo sát phần GNU grep

## Yêu cầu của khảo sát
- Tìm hiểu và khảo sát hoạt động của các thuật toán Fast  string search và regex, minh họa qua ứng dụng GNU grep
- Các bạn sẽ khảo sát độ phức tạp của thuật toán string search theo 03 tham số:
  - m: Độ dài của chuỗi cần tìm
  - k: số hàng trong file chứa chuỗi lớn
  - n: độ dài tối đa của một hàng trong file lớn.
 - Có 02 tình huống cần khảo sát:
1. File chứa nhiều chuỗi, có độ dài xấp xỉ nhau.
2. File chứa rất ít chuỗi nhưng mỗi chuỗi rất dài.
 - Với mỗi tình huống, sinh viên cho độ dài của chuỗi cần tìm (m) tăng dần từ 10 đến 1000 để khảo sát độ phức tạp, theo cả 03 tham số.
- Phần regex tìm hiểu cấu trúc của cú pháp regex và chạy thử một vài mẫu regex có thể thường dùng trong thực tế. Sau đó đo thử thời gian grep tìm kiếm regex trên file lớn.
- Chú ý với regex chỉ đo thời gian để tham khảo, không cần tính độ phức tạp.

## Quá trình khảo sát
- Trong TH1 có 2 trường hợp con cần thực nghiệm:
  1. Cố định k và tăng m và n (k = 2000).
  2. Cố định n và tăng kích thước cua k và m (n = 400000).
- Trong TH2 có 1 trường hợp con cần thực nghiệm:
  1. Cố định k và tăng m và n (k = 5, n rất lớn).
  2. Do k ít nên nhóm em sẽ bỏ qua việc thực nghiệm tham số k trong trường hợp này.

- Thực hiện tạo ra 50 file cho tham số m dùng cho mọi thực nghiệm với tham số k và n.
- Thực hiện tạo 50 file cho tham số n cho mỗi TH.
- Thực hiện tạo 50 file cho tham số k.
- Các file chỉ chứa kí tự là trong bảng chữ cái tiếng anh (cả hoa và thường) và các chữ số, file không có kí tự đặc biệt khác vì để tránh trường hợp invalid range.
- Mỗi file của tham số n và k đều sẽ được test với 50 file của m.
- Đo dung lượng Ram và đĩa cứng và nhiệt độ cùng lúc trong lúc chạy grep.
- Lưu toàn bộ kết quả và vào thư mục result ứng với giá trị k và n tương ứng trong các trường họp, file kết quả có 3 loại:
  1. test_(size m).txt - lưu kết quả về thời gian chạy và dung lượng RSS mà grep sử dụng
  2. test_(size m)_disk.txt - lưu kết quả do dung lượng của thư mục /tmp.
  3. test_(size m)_sensors.txt - Lưu kết quả của nhiệt độ trước lúc chạy và dung lượng Ram mà grep sử dụng.

## Cấu trúc file trong cây thư mục.
- TH1: lưu các file dùng cho thực nghiệm với tham số n và k trong trường hợp 1.
- TH2: lưu các file dùng cho thực nghiệm với tham số n trong trường hợp 2.
- result: lưu các file kết quả của toàn bộ quá trình thực nghiệm.
- script: chứa các file shell dùng cho quá trình thực nghiệm.
  - fix.sh - tự động chạy lại các test case không đo được dung lượng Ram.
  - k.sh - thực hiện lệnh grep với tham số k.
  - n.sh - thực hiện lệnh grep với tham số n.
  - n_TH1.sh - thực nghiệm tham số n trong TH1.
  - n_TH2.sh - thực nghiệm tham số n trong TH2.
  - k_TH1.sh - thực nghiệm tham số k trong TH1.

- sheet: chứa bảng tính kết quả đo đạc
- test: lưu các file của tham số m
- Makefile: dùng để thực hiện tự động toàn bộ quá trình thực nghiệm
- grep.sh: file shell thực thi chính
- init.sh: tạo các thư mục dùng cho việc lưu kết quả trong thư mục result
- make_csv.cpp: file cpp dùng để tự động tạo file csv
- make_test.csv: file cpp dùng để tạo tự động các file của toàn bộ tham số trong cả 2 trường hơp.
- measure_ram.sh: đo dung lượng Ram và đĩa cứng mà grep sử dụng trong lúc chạy.
- remove_end.sh: loại bỏ hàng cuối dùng trong các file sensors, do lúc do dung lượng Ram sẽ có trường hơp bắt được lệnh grep lúc nó chuẩn bị kết thúc.

## Thực nghiệm
- Lệnh thực nghiệm: sudo make auto NUM_FILE=50
  - Có thẻ thay số 50 bằng với sô lần chạy mà mình mong muốn cho mỗi tham số.
- m: file ngắn nhất có 2000 từ và tăng 2000 từ mỗi file.
- n - TH1: file ngắn nhất có 505000 kí tự trên 1 hàng và tăng 5000 kí tự một hàng mỗi file (k = 2000).
- n - TH2: file ngắn nhất có 10000000 kí tự trên 1 hàng và tăng 10000000 kí tự một hàng mỗi file (k = 5).
- k - TH1: file ngắn nhất có 100 hàng và tăng 100 hàng mỗi file (n = 400000).
- Toàn bộ 50 file của m sẽ được dùng để chạy với từng file của tham số n và k
  - Số lần chạy grep TH1: 50x50 + 50x50 = 5000 (lần)
  - Số lần chạy grep TH2: 50x50 = 2500 (lần)
  - 50 chỉ là con số ví dụ, nó là số file của tham số m, n, k trong mọi trường hợp và có thể thay đổi tùy theo ý muốn của người sử dụng.
