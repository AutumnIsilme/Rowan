pub struct Error {
    pub error_code: u32,
    pub line_number: u32,
    pub column_number: u32,
}

impl Error {
    pub fn create(error_code: u32, line_number: u32, column_number: u32,) -> Error {
        return Error {
            error_code: error_code,
            line_number: line_number,
            column_number: column_number,
        };
    }
}