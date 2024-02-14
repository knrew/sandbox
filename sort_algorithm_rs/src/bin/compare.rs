use std::env;
use std::error::Error;
use std::time;

#[allow(unused_imports)]
use sort_algorithm::{utils, *};

fn main() -> Result<(), Box<dyn Error>> {
  let args: Vec<String> = env::args().collect();
  let config = Config::new(&args);

  let sequence = utils::read_file(config.sequence_file)?;
  let answer = utils::read_file(config.answer_file)?;

  print!("intrinsic: ");
  let (elapsed, sort_success) = measure_time(&sequence, &answer, |v| v.sort());
  println!("{:?}", elapsed);
  if !sort_success {
    println!("failed to sort.");
  }

  print!("quick: ");
  let (elapsed, sort_success) = measure_time(&sequence, &answer, quick_sort);
  println!("{:?}", elapsed);
  if !sort_success {
    println!("failed to sort.");
  }

  print!("merge: ");
  let (elapsed, sort_success) = measure_time(&sequence, &answer, merge_sort);
  println!("{:?}", elapsed);
  if !sort_success {
    println!("failed to sort.");
  }

  print!("bubble: ");
  let (elapsed, sort_success) = measure_time(&sequence, &answer, bubble_sort);
  println!("{:?}", elapsed);
  if !sort_success {
    println!("failed to sort.");
  }

  print!("insertion: ");
  let (elapsed, sort_success) = measure_time(&sequence, &answer, insertion_sort);
  println!("{:?}", elapsed);
  if !sort_success {
    println!("failed to sort.");
  }

  print!("selection: ");
  let (elapsed, sort_success) = measure_time(&sequence, &answer, selection_sort);
  println!("{:?}", elapsed);
  if !sort_success {
    println!("failed to sort.");
  }

  print!("heap: ");
  let (elapsed, sort_success) = measure_time(&sequence, &answer, heap_sort);
  println!("{:?}", elapsed);
  if !sort_success {
    println!("failed to sort.");
  }

  Ok(())
}

fn measure_time<F: Fn(&mut Vec<i32>)>(
  sequence: &Vec<i32>,
  answer: &Vec<i32>,
  sort_func: F,
) -> (std::time::Duration, bool) {
  let mut vec = sequence.clone();
  let timer = time::Instant::now();
  sort_func(&mut vec);
  let elapsed = timer.elapsed();
  (elapsed, &vec == answer)
}

struct Config {
  sequence_file: String,
  answer_file: String,
}

impl Config {
  fn new(args: &[String]) -> Config {
    let sequence_file = args[1].clone();
    let answer_file = args[2].clone();

    Config {
      sequence_file,
      answer_file,
    }
  }
}
