#include <aws/core/Aws.h> 
#include <aws/core/auth/AWSCredentialsProvider.h> 
#include <aws/sqs/SQSClient.h> 
#include <aws/sqs/model/SendMessageRequest.h> 
#include <aws/sqs/model/SendMessageResult.h> 
#include <iostream> 

int main(int argc, char** argv) 
{ 
    Aws::SDKOptions options; 
    Aws::InitAPI(options); 
    Aws::Client::ClientConfiguration clientConfig; 
    clientConfig.region = "ap-northeast-2"; 
    { 
        Aws::String queue_url = "endpoint_of_your_sqs" ; 
        Aws::String msg_body = "input_you_want_to_send"; 
        Aws::String msg_group_id = "input_msg_group_id"; 
        Aws::SQS::SQSClient sqs(Aws::Auth::AWSCredentials("your_access_key", "your_secret_key"), clientConfig); 
        Aws::SQS::Model::SendMessageRequest sm_req; 
        sm_req.SetQueueUrl(queue_url); 
        sm_req.SetMessageGroupId(msg_group_id); 
        sm_req.SetMessageBody(msg_body); 
        sm_req.SetMessageDeduplicationId("unique_value_for_deduplication"); 
        
        auto sm_out = sqs.SendMessage(sm_req); 
        if (sm_out.IsSuccess()) 
        { 
            std::cout << "Successfully sent message to " << queue_url << std::endl; 
        } else { 
            std::cout << "Error sending message to " << queue_url << ": " << sm_out.GetError().GetMessage() << std::endl; 
        } 
     } 
   
     Aws::ShutdownAPI(options); 
     system("PAUSE"); 
     return 0; 
   }
