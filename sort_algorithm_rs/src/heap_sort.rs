pub fn heap_sort(vec: &mut Vec<i32>) {
  heap_sort_impl(vec, 0, vec.len() - 1);
}

pub fn heap_sort_impl(vec: &mut Vec<i32>, first: usize, last: usize) {
  make_heap(vec, first, last);
  sort_heap(vec, first, last);
}

fn make_heap(vec: &mut Vec<i32>, first: usize, last: usize) {
  let len = last - first + 1;

  for i in (0..len / 2).rev() {
    down_heap(vec, first, last, i);
  }
}

fn sort_heap(vec: &mut Vec<i32>, first: usize, last: usize) {
  for i in (first + 1..last + 1).rev() {
    vec.swap(first, i);
    down_heap(vec, first, i - 1, 0);
  }
}

fn down_heap(vec: &mut Vec<i32>, first: usize, last: usize, top: usize) {
  let len = last - first + 1;

  let value = vec[first + top];

  let mut parent = top;

  while 2 * parent + 1 < len {
    let mut child = 2 * parent + 1;

    if child + 1 < len && vec[first + child] < vec[first + child + 1] {
      child += 1;
    }

    if value >= vec[first + child] {
      break;
    }

    vec[first + parent] = vec[first + child];

    parent = child;
  }

  vec[first + parent] = value;
}
