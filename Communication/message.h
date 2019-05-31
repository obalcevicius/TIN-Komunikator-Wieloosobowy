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
	  static Message * createMessage(Header * head);
	  //tu są oba schematy deserializacji uwzględnione
	  static Message * transform(PlainMessage oldMessage);

	  static Message * deserialize(PlainMessage mess);
	  virtual void virt_deserialize(PlainMessage mess) = 0;
	  virtual PlainMessage serialize() = 0;
	  virtual MessageType typeCheck() = 0;
	  //void send(NodeInfo node);
};
  
} // namespace Communication

#endif //MESSAGE_H
