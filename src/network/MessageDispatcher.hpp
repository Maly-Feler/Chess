class MessageDispatcher
{
public:
    void dispatch(
        const NetworkMessage& message,
        connection_hdl client);
};