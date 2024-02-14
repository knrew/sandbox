use std::error::Error;
use std::fs;
use std::io::prelude::*;
use std::io::BufReader;

pub fn read_file(file_name: String) -> Result<Vec<i32>, Box<dyn Error>> {
  let f = fs::File::open(file_name)?;

  let reader = BufReader::new(f);

  let mut result: Vec<i32> = vec![];

  for line in reader.lines() {
    let n: i32 = line?.trim().parse()?;
    result.push(n);
  }

  Ok(result)
}
