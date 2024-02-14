pub fn insertion_sort(vec: &mut Vec<i32>) {
  for i in 0..vec.len() {
    let mut j = i;
    while j > 0 && vec[j] < vec[j - 1] {
      vec.swap(j, j - 1);
      j -= 1;
    }
  }
}
