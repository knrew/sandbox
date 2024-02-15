pub fn insertion_sort(vec: &mut Vec<i32>) {
  for i in 0..vec.len() {
    for j in (1..i + 1).rev() {
      if vec[j] < vec[j - 1] {
        vec.swap(j, j - 1);
      }
    }
  }
}
