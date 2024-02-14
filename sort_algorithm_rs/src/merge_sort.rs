#[allow(unused_imports)]
use std::collections::LinkedList;

pub fn merge_sort(vec: &mut Vec<i32>) {
  merge_sort_array(vec, 0, vec.len() - 1);
  // merge_sort_linked_list(vec);
}

#[allow(dead_code)]
fn merge_sort_array(vec: &mut Vec<i32>, l: usize, h: usize) {
  if l >= h {
    return;
  }

  let mid = l + (h - l) / 2;

  merge_sort_array(vec, l, mid);

  merge_sort_array(vec, mid + 1, h);

  let mut tmp: Vec<i32> = vec![];

  for i in 0..mid + 1 {
    tmp.push(vec[i]);
  }

  for i in (mid + 1..h + 1).rev() {
    tmp.push(vec[i]);
  }

  let mut i = l;
  let mut j = h;
  for k in l..h + 1 {
    if tmp[i] <= tmp[j] {
      vec[k] = tmp[i];
      i += 1;
    } else {
      vec[k] = tmp[j];
      j -= 1;
    }
  }
}

#[allow(dead_code)]
fn merge_sort_linked_list(_vec: &mut Vec<i32>) {}
