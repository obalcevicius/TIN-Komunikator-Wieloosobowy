#ifndef MESSAGE_H
#define MESSAGE_H

#include "plainMessage.h"
#include "messageType.h"

namespace Communication {

/**
 * @brief Base class for all messages
 */
class Message 
{    
	  static Message * createMessage(Header * head);
	  //tu są oba schematy deserializacji uwzględnione
	  static Message * transform(PlainMessage oldMessage);

	  static Message * deserialize(PlainMessage mess);
	  virtual void virt_deserialize(PlainMessage mess) = 0;
	  virtual PlainMessage serialize() = 0;
	  virtual MessageType presentType() = 0;
	  //void send(NodeInfo node);
};
  
} // namespace Communication

#endif //MESSAGE_H