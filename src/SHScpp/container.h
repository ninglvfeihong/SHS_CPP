/*
 * container.h
 *
 *  Created on: 22 Mar 2016
 *      Author: Xiao WANG
 */

#ifndef SHSCPP_CONTAINER_H_
#define SHSCPP_CONTAINER_H_
#include <string>
#include <list>
#include "log.h"
#include "serialPort.h"
#include "rabbitMQSender.h"
#include "myMQ.h"
#include "conf.h"
//ninglvfeihong:below declare is important for include each other
namespace SHS {
	class Container;
}

#include "cmd/cmd.h"
#include "Lookup.h"
#include "Bindings.h"
namespace SHS {
class Container {
public:
	Container(Conf &conf);
	virtual ~Container();
	Cmd* getCmdObj(std::string & objName);
	Cmd* getCmdObj(const char* objName);
	void regActCmd(Cmd* cmdObj);
	void delActCmd(Cmd* cmdObj);
	void lockContainer();
	void unlockContainer();
	void setSerialSenderMQ(MyMQ<std::string>* pSerialSenderMQ);
	void setRabbitMQSenderMQ(MyMQ<Json::Value> * pRabbitMQSenderMQ);
	void setRabbitMQAnalyserMQ(MyMQ<Json::Value> * pRabbitMQAnalyserMQ);
	std::list<Cmd *> actCmds;
	MyMQ<std::string>* pSerialSenderMQ;
	MyMQ<Json::Value> * pRabbitMQSenderMQ;
	MyMQ<Json::Value> * pRabbitMQAnalyserMQ;
	Conf* pConf;
	Lookup lookup;
	Bindings bindings;

private:
	pthread_mutex_t containersMutex;
	void delayInitCmdObj();
};

} /* namespace SHS */

#endif /* SHSCPP_CONTAINER_H_ */
