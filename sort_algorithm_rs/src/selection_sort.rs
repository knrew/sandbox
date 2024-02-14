pub fn selection_sort(vec: &mut Vec<i32>) {
  for i in 0..vec.len() - 1 {
    let mut min_index = i;

    for j in i + 1..vec.len() {
      if vec[j] < vec[min_index] {
        min_index = j;
      }
    }

    vec.swap(i, min_index);
  }
}
