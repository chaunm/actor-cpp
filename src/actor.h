/*
 * actor.h
 *
 *  Created on: Sep 13, 2017
 *      Author: chaunm
 */

#ifndef ACTOR_H_
#define ACTOR_H_

typedef void (*ACTORCALLBACKFN)(void*);
typedef void* CallbackParam;

typedef struct tagACTOREVENT {
	char* event;
	CallbackParam callbackParam;
	struct tagACTOREVENT* NextEvent;
}ACTOREVENT, *PACTOREVENT;

typedef struct tagACTORCALLBACK {
	char* event;
	ACTORCALLBACKFN callbackFn;
	char callbackType;
	struct tagACTORCALLBACK* nextCallback;
} ACTORCALLBACK, *PACTORCALLBACK;

typedef struct tagACTOR {
	struct mosquitto* client;
	int DeliveredToken;
	PACTOREVENT pEvent;
	PACTORCALLBACK pActorCallback;
	char connected;
	char* guid;
	char* psw;
	char* host;
	WORD port;
}ACTOR, *PACTOR;

class actor {
public:
	actor();
	virtual ~actor();
	/* make an unique guid for actor by combine a prefix with a generated uuid
	 * the result guid has the from of prefix-generated-uuid
	 */
	char* MakeGuid(char* prefix);
	/* make topic name for actor to public or subcribe
	 * A topic name has form of actor's guid/topic
	 * guid: Actor's guid
	 * topic: topic to subscribe or publish, topic can be
	 * 		/:request/...
	 * 		/:response
	 * 		/:event
	 */
	char* MakeTopicName(const char* messageType, const char* guid, char* topic);
	/* register callback for actor
	 * event: event to trigger callback
	 * callback:
	 * 		fncallback to call when event occur (void fncallback(PVOID* pParam)
	 * 			pParam is a pointer to a data that user can pass when callback occur
	 * 			this param must be allocated to pass to callback and will be free after callback has been processed by actor
	 * callbackType:
	 * 		CALLBACK_ONCE: callback is only triggered one time and will be free.
	 * 		CALLBACK_RETAIN: callback is triggered every time event occurs
	 */
	void RegisterCallback(PACTOR pActor, const char* event, ACTORCALLBACKFN callback, char callbackType);
	/* Create an event for triggering callback
	 * pActor: pointer to actor to emit event
	 * event: name of event
	 * pParam: pointer to data that should be processed whwne callback
	 */
	void EmitEvent(PACTOR pActor, const char* event, void* pParam);
	/* ActorProcessEvent: Process event message
	 * This function must be called in a indefinite loop
	 * pActor: pointer to actor to process event
	 */
	void ProcessEvent(PACTOR pActor);
	/* create an actor with guid and psw
	 * After created, actor will connect to the host (internal) and subscribe to topics /:request/# and :/response
	 * result will be an valid actor if valid connection is created
	 * result NULL if cannot create an actor or cannot connect to internal host
	 */
	PACTOR Create(char* guid, char* psw, char* host, WORD port);
	/* Delete an actor */
	void Delete(PACTOR pActor);
	/* Actor publish a message to topicName and trigger a callback for response handling */
	void Send(PACTOR pActor, char* topicName, char* message, ACTORCALLBACKFN callback, char bIdGen, char* type);
	/* Get uuid name of an actor */
	char* GetGuid(PACTOR pActor);
};

#endif /* ACTOR_H_ */
