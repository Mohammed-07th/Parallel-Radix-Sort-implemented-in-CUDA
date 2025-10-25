# Radix Sort (CUDA)

A simple parallel Radix Sort implemented in **CUDA**, demonstrating how to sort integers on the GPU using shared memory.  
This project can be compiled locally using `nvcc` or run directly in **Google Colab** with GPU runtime enabled.

---

## 🧩 Description
Parallel Radix Sort in CUDA that sorts a fixed-size integer array (`N = 16`) by processing digits one by one using shared memory.  
It prints the array after each iteration to visualize the sorting process.  
Ideal for learning GPU programming, thread synchronization, and CUDA shared memory operations.

---

## 🧠 Key Features
- Fully GPU-based sorting kernel  
- Uses shared memory for intermediate data  
- Prints intermediate sorting stages (per digit pass)  
- Easy to run on Google Colab or any CUDA-capable system  

---

## ⚙️ Requirements
- NVIDIA GPU with CUDA support  
- [CUDA Toolkit](https://developer.nvidia.com/cuda-toolkit) installed (for `nvcc`)  
- (Optional) Google Colab with GPU runtime enabled  

---

## 🚀 Running Locally
```bash
# Compile
nvcc -o radix_sort radix_sort.cu

# Run
./radix_sort
