pub fn heap_sort(vec: &mut Vec<i32>) {
  for i in (1..vec.len() / 2 + 1).rev() {
    down_heap(vec, i, vec.len());
  }

  for i in (2..vec.len() + 1).rev() {
    vec.swap(1 - 1, i - 1);
    down_heap(vec, 1, i - 1);
  }
}

fn down_heap(vec: &mut Vec<i32>, from: usize, to: usize) {
  let val = vec[from - 1];

  let mut i = from;
  while i <= to / 2 {
    let mut j = i * 2;
    if j + 1 <= to && vec[j - 1] < vec[j] {
      j += 1;
    }

    if val >= vec[j - 1] {
      break;
    }

    vec[i - 1] = vec[j - 1];
    i = j;
  }

  vec[i - 1] = val;
}
