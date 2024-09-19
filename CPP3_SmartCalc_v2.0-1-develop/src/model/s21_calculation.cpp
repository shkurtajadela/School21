#include "s21_calculation.h"

namespace s21 {

// Устанавливает значение переменной x_.
void Calculation::SetX(double x) noexcept { x_ = x; }

// Преобразует строку в число и устанавливает его как значение x_.
void Calculation::SetX(const std::string& x_str) noexcept {
  double x = NAN;
  int shift = 0;
  std::string str = x_str;
  TrimSpaces(str);  // Убирает пробелы в начале и конце строки.
  CommaToDot(str);  // Заменяет запятые на точки в строке.
  sscanf(str.c_str(), "%lf%n", &x, &shift);
  if (shift == 0 || shift != static_cast<int>(str.size()))
    SetX(NAN);
  else
    SetX(x);
}

// Устанавливает выражение, которое необходимо вычислить.
void Calculation::SetExpression(const std::string& input) noexcept {
  expr_ = input;
  status_ = NEW_EXPRESSION;
}

// Устанавливает режим работы тригонометрических функций в радианах.
void Calculation::SetRadian() noexcept { trig_value_ = RAD; }

// Устанавливает режим работы тригонометрических функций в градусах.
void Calculation::SetDegree() noexcept { trig_value_ = DEG; }

// Возвращает текущее значение переменной x_.
double Calculation::GetX() const noexcept { return x_; }

// Возвращает текущее выражение для вычисления.
const std::string Calculation::GetExpression() const noexcept { return expr_; }

// Возвращает текущий режим тригонометрических функций (радианы или градусы).
Calculation::TrigType Calculation::GetTrigValue() const noexcept {
  return trig_value_;
}

// Возвращает текущий статус вычисления.
Calculation::Status Calculation::GetStatus() const noexcept { return status_; }

// Выполняет вычисление выражения и возвращает результат.
double Calculation::GetResult() {
  if (status_ == NEW_EXPRESSION)
    Reset();  // Сброс состояния при новом выражении.
  if (status_ == READY) Parse();  // Разбирает выражение на токены.
  if (status_ == PARSED || status_ == COMPLETED)
    Calculate();  // Вычисляет результат.
  return result_;
}

// Устанавливает значение x и выполняет вычисление выражения.
double Calculation::GetResult(double x) {
  SetX(x);
  return GetResult();
}

// Устанавливает выражение и выполняет его вычисление.
double Calculation::GetResult(const std::string& input) {
  SetExpression(input);
  return GetResult();
}

// Устанавливает выражение и значение x, после чего выполняет вычисление.
double Calculation::GetResult(const std::string& input, double x) {
  SetX(x);
  return GetResult(input);
}

// Устанавливает выражение и значение x (в строковом виде), затем выполняет
// вычисление.
double Calculation::GetResult(const std::string& input, const std::string& x) {
  SetX(x);
  return GetResult(input);
}

// Сбрасывает все внутренние состояния и очищает стеки для нового вычисления.
void Calculation::Reset() {
  result_ = NAN;
  status_ = READY;
  prev_ = UNDEF;
  while (!stack_.empty()) stack_.pop();
  while (!calc_stack_.empty()) calc_stack_.pop();
  output_queue_.clear();
}

// Разбирает выражение на токены и преобразует его в обратную польскую нотацию.
void Calculation::Parse() {
  TrimSpaces(expr_);  // Убирает лишние пробелы из выражения.
  if (expr_.empty()) {
    status_ = EMPTY;
    return;
  }
  CommaToDot(expr_);  // Заменяет запятые на точки.
  iter_ = expr_.begin();
  while (iter_ != expr_.end()) {
    if (*iter_ == ' ') {
      iter_++;
    } else {
      CheckHiddenMultiplication();  // Проверяет необходимость добавления
                                    // умножения.
    }
    ParseToken();  // Разбирает текущий токен.
    if (status_ == PARSE_ERROR) return;
  }
  while (!stack_.empty()) {
    if (stack_.top() == RIGHT_PAR || stack_.top() == LEFT_PAR) {
      status_ = PARSE_ERROR;
      return;
    }
    if (IsBinaryOperator(stack_.top()) || IsUnaryOperator(stack_.top())) {
      output_queue_.push_back(
          Token{stack_.top(), NAN});  // Добавляет оператор в выходную очередь.
      stack_.pop();
    }
  }
  status_ = PARSED;  // Изменяет статус на "разобранный".
}

// Выполняет вычисление выражения, преобразованного в обратную польскую нотацию.
void Calculation::Calculate() {
  double x1 = NAN, x2 = NAN;
  for (Token token : output_queue_) {
    if (token.type == NUM) {
      calc_stack_.push(token.number);  // Добавляет число в стек вычислений.
    } else if (token.type == X) {
      calc_stack_.push(x_);  // Добавляет значение переменной x в стек.
    } else if (IsFunction(token.type) || IsUnaryOperator(token.type)) {
      if (calc_stack_.empty()) {
        status_ = CALCULATE_ERROR;
        return;
      }
      CalculateUnaryOrFunction(
          token
              .type);  // Вычисляет значение для унарного оператора или функции.
    } else if (IsBinaryOperator(token.type)) {
      if (calc_stack_.empty()) {
        status_ = CALCULATE_ERROR;
        return;
      }
      x2 = calc_stack_.top();
      calc_stack_.pop();
      if (calc_stack_.empty()) {
        status_ = CALCULATE_ERROR;
        return;
      }
      x1 = calc_stack_.top();
      calc_stack_.pop();
      calc_stack_.push(GetBinaryCallback(token.type)(
          x1, x2));  // Вычисляет значение для бинарного оператора.
    }
  }
  result_ = calc_stack_.top();
  calc_stack_.pop();
  status_ = COMPLETED;  // Изменяет статус на "завершён".
}

/* Вспомогательные функции */

// Вычисляет значение унарного оператора или функции.
void Calculation::CalculateUnaryOrFunction(TokenType token_type) {
  double x1 = calc_stack_.top();
  calc_stack_.pop();
  if (trig_value_ == DEG) {
    if (IsFunction(token_type) &&
        GetFunctionType(token_type) == TRIGONOMICAL_STRAIGHT)
      calc_stack_.push(GetUnaryCallback(token_type)(x1 * M_PI / 180.0));
    else if (IsFunction(token_type) &&
             GetFunctionType(token_type) == TRIGONOMICAL_ARC)
      calc_stack_.push(GetUnaryCallback(token_type)(x1) * 180.0 / M_PI);
    else
      calc_stack_.push(GetUnaryCallback(token_type)(x1));
  } else
    calc_stack_.push(GetUnaryCallback(token_type)(x1));
}

// Разбирает текущий токен выражения.
void Calculation::ParseToken() {
  bool parsed = false;
  std::string::const_iterator init = iter_;
  parsed = CheckNumber(init);  // Проверяет, является ли токен числом.
  if (!parsed)
    parsed = CheckX(init);  // Проверяет, является ли токен переменной x.
  if (!parsed)
    parsed = CheckFunction(init);  // Проверяет, является ли токен функцией.
  if (!parsed)
    parsed = CheckLeftParenthesis(
        init);  // Проверяет, является ли токен левой скобкой.
  if (!parsed)
    parsed = CheckUnarOperator(
        init);  // Проверяет, является ли токен унарным оператором.
  if (!parsed)
    parsed = CheckOperator(init);  // Проверяет, является ли токен оператором.
  if (!parsed)
    parsed = CheckRightParenthesis(
        init);  // Проверяет, является ли токен правой скобкой.
  if (!parsed)
    status_ =
        PARSE_ERROR;  // Устанавливает статус ошибки, если токен не распознан.
}

// Проверяет наличие скрытого умножения в выражении.
void Calculation::CheckHiddenMultiplication() {
  if ((prev_ == NUM &&
       (ParseFunction(iter_) != UNDEF || *iter_ == '(' || *iter_ == 'x')) ||
      (prev_ == X && *iter_ == '(') || (prev_ == RIGHT_PAR && *iter_ == '(') ||
      (prev_ == RIGHT_PAR && IsFunction(ParseFunction(iter_)))) {
    while (!stack_.empty() &&
           ((IsBinaryOperator(stack_.top()) &&
             GetPriority(stack_.top()) >= GetPriority(MULT)) ||
            IsUnaryOperator(stack_.top()))) {
      output_queue_.push_back(Token{stack_.top(), NAN});
      stack_.pop();
    }
    stack_.push(MULT);  // Вставляет оператор умножения в стек.
    prev_ = MULT;
  }
}

// Проверяет, является ли токен числом.
bool Calculation::CheckNumber(std::string::const_iterator input) {
  if (isdigit(*input) || *input == '.') {
    int shift = 0;
    double number = 0.0;
    sscanf(&input[0], "%lf%n", &number, &shift);
    if (shift > 0 && prev_ != X && prev_ != NUM && prev_ != RIGHT_PAR) {
      output_queue_.push_back(Token{NUM, number});
      prev_ = NUM;
      iter_ += shift;
      return true;
    }
  }
  return false;
}

// Проверяет, является ли токен переменной x.
bool Calculation::CheckX(std::string::const_iterator input) {
  if (*input == 'x' && prev_ != X && prev_ != RIGHT_PAR) {
    output_queue_.push_back(Token{X, NAN});
    prev_ = X;
    iter_++;
    return true;
  }
  return false;
}

// Проверяет, является ли токен функцией.
bool Calculation::CheckFunction(std::string::const_iterator input) {
  TokenType value = UNDEF;
  value = ParseFunction(input);
  if (value != UNDEF && prev_ != RIGHT_PAR && prev_ != X && prev_ != NUM) {
    stack_.push(value);
    prev_ = value;
    iter_ += GetString(value).size();
    return true;
  }
  return false;
}

// Разбирает строку и определяет тип функции.
Calculation::TokenType Calculation::ParseFunction(
    std::string::const_iterator input) {
  for (const auto& [key, value] : functions) {
    size_t shift = GetString(key).size();
    if (!strncmp(&input[0], GetString(key).data(), shift) &&
        *(input + shift) == '(') {
      return key;
    }
  }
  return UNDEF;
}

// Проверяет, является ли токен левой скобкой.
bool Calculation::CheckLeftParenthesis(std::string::const_iterator input) {
  if (*input == '(') {
    stack_.push(LEFT_PAR);
    prev_ = LEFT_PAR;
    iter_++;
    return true;
  }
  return false;
}

// Проверяет, является ли токен унарным оператором.
bool Calculation::CheckUnarOperator(std::string::const_iterator input) {
  if (prev_ != NUM && prev_ != X && prev_ != RIGHT_PAR) {
    for (const auto& [key, value] : unary_operators) {
      if (!strncmp(&input[0], GetString(key).data(), GetString(key).size()) &&
          *(input + GetString(key).size()) != ' ') {
        stack_.push(key);
        prev_ = key;
        iter_ += GetString(key).size();
        return true;
      }
    }
  }
  return false;
}

// Проверяет, является ли токен оператором.
bool Calculation::CheckOperator(std::string::const_iterator input) {
  for (const auto& [key, value] : operators) {
    if (!strncmp(&input[0], GetString(key).data(), GetString(key).size())) {
      while (
          !stack_.empty() &&
          ((IsBinaryOperator(stack_.top()) &&
            (GetPriority(stack_.top()) > GetPriority(key) ||
             (GetPriority(stack_.top()) == GetPriority(key) && key != POW))) ||
           IsUnaryOperator(stack_.top()))) {
        output_queue_.push_back(Token{stack_.top(), NAN});
        stack_.pop();
      }
      stack_.push(key);
      prev_ = key;
      iter_ += GetString(key).size();
      return true;
    }
  }
  return false;
}

// Проверяет, является ли токен правой скобкой.
bool Calculation::CheckRightParenthesis(std::string::const_iterator input) {
  if (*input == ')') {
    while (!stack_.empty() && stack_.top() != LEFT_PAR &&
           (IsBinaryOperator(stack_.top()) || IsUnaryOperator(stack_.top()))) {
      output_queue_.push_back(Token{stack_.top(), NAN});
      stack_.pop();
    }
    if (stack_.empty())
      status_ = PARSE_ERROR;
    else if (stack_.top() == LEFT_PAR) {
      stack_.pop();
      if (!stack_.empty() && IsFunction(stack_.top())) {
        output_queue_.push_back(Token{stack_.top(), NAN});
        stack_.pop();
      }
      while (!stack_.empty() && IsUnaryOperator(stack_.top())) {
        output_queue_.push_back(Token{stack_.top(), NAN});
        stack_.pop();
      }
    }
    prev_ = RIGHT_PAR;
    iter_++;
    return true;
  }
  return false;
}

// Возвращает приоритет оператора.
int Calculation::GetPriority(TokenType value) {
  return std::get<2>(operators.at(value));
}

// Возвращает строковое представление токена.
const std::string Calculation::GetString(TokenType value) {
  if (IsBinaryOperator(value)) return std::get<0>(operators.at(value));
  if (IsUnaryOperator(value)) return std::get<0>(unary_operators.at(value));
  return std::get<0>(functions.at(value));
}

// Возвращает callback для выполнения унарного оператора или функции.
Calculation::UnaryCallback Calculation::GetUnaryCallback(TokenType value) {
  if (IsUnaryOperator(value)) return std::get<1>(unary_operators.at(value));
  return std::get<1>(functions.at(value));
}

// Возвращает callback для выполнения бинарного оператора.
Calculation::BinaryCallback Calculation::GetBinaryCallback(TokenType value) {
  return std::get<1>(operators.at(value));
}

// Возвращает тип функции (например, тригонометрическая функция).
Calculation::FuncType Calculation::GetFunctionType(TokenType value) {
  return std::get<2>(functions.at(value));
}

// Проверяет, является ли токен бинарным оператором.
bool Calculation::IsBinaryOperator(TokenType value) noexcept {
  return value >= SUM && value <= MOD;
}

// Проверяет, является ли токен унарным оператором.
bool Calculation::IsUnaryOperator(TokenType value) noexcept {
  return value >= PLUS && value <= MINUS_ALT;
}

// Проверяет, является ли токен функцией.
bool Calculation::IsFunction(TokenType value) noexcept {
  return value >= SQRT && value <= ATAN;
}

/* Вспомогательные функции */

// Удаляет пробелы в начале и конце строки и сокращает последовательности
// пробелов до одного символа.
void Calculation::TrimSpaces(std::string& str) {
  std::string::iterator iter = str.begin();
  if (!str.empty()) {
    while (*iter == ' ') iter++;
    str.erase(str.begin(), iter);
  }

  iter = str.end();
  if (!str.empty()) {
    while (*(iter - 1) == ' ') iter--;
    str.erase(iter, str.end());
  }

  for (iter = str.begin(); iter != str.end(); iter++) {
    if (*iter == ' ' && *(iter + 1) == ' ') iter = str.erase(iter) - 1;
  }
}

// Заменяет все запятые в строке на точки.
void Calculation::CommaToDot(std::string& str) {
  std::string::iterator iter = str.begin();
  for (iter = str.begin(); iter != str.end(); iter++) {
    if (*iter == ',') *iter = '.';
  }
}

}  // namespace s21
