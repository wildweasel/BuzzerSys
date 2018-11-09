struct LED{

  int pin;
  String color;
  
  LED(const int pin, const String color) : pin(pin), color(color){
  }

  String getColor(){
    return color;
  }

  void init(){
    pinMode(pin, OUTPUT);
  }

  void on(){
    digitalWrite(pin, HIGH);
  }

  void off(){
    digitalWrite(pin, LOW);
  }
  
};
