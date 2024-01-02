import random

# Số lượng phần tử
num_elements = 15000

# Tạo dãy số ngẫu nhiên
random_numbers = [random.randint(1, 1000000) for _ in range(num_elements)]

# Lưu vào file .txt
with open("input_data.txt", "w") as file:
    for number in random_numbers:
        file.write(str(number) + " ")

print("File input_data.txt đã được tạo thành công.")
