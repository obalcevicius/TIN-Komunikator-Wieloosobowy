#ifndef MESSAGE_H
#define MESSAGE_H

#include "plainmessage.h"
#include "messageType.h"

namespace Communication {

/**
 * @brief Base class for all messages
 */
class Message 
{    
	  public:
	  static Message * createMessage(Header * t_head);
	  //tu są oba schematy deserializacji uwzględnione
	  static Message * transform(PlainMessage t_oldMessage);

	  static Message * deserialize(PlainMessage t_mess);
	  virtual void virt_deserialize(PlainMessage t_mess) = 0;
	  virtual PlainMessage serialize() = 0; //a tu move konstruktor
	  virtual MessageType typeCheck() = 0;
	  //void send(NodeInfo node);
};
  
} // namespace Communication

#endif //MESSAGE_H
