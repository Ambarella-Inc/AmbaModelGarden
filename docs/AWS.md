# AWS

Amazon SageMaker is a fully managed machine learning (ML) service. With SageMaker, data scientists and developers can quickly and confidently build, train, and deploy ML models into a production-ready hosted environment. It provides a UI experience for running ML workflows that makes SageMaker ML tools available across multiple integrated development environments (IDEs) [SageMaker](https://docs.aws.amazon.com/sagemaker/latest/dg/whatis.html) 

The following describes the architecture for training and serve [Train](https://docs.aws.amazon.com/sagemaker/latest/dg/how-it-works-training.html)

## Pre-requisites

### Installing the AWS Command Line Tool

To get started, users must install the AWS CLI tool that allows interaction with AWS services with the command line shell.

1. Install the CLI [Install](https://docs.aws.amazon.com/cli/latest/userguide/getting-started-install.html)

2. Configure the CLI [Configure](https://docs.aws.amazon.com/cli/latest/userguide/cli-chap-configure.html)

### Creating S3 bucket 

Users must create an S3 bucket to store their training input data and output artifacts. 

1. Setting up the bucket [Setup](https://docs.aws.amazon.com/AmazonS3/latest/userguide/setting-up-s3.html)


        ! Please ensure the bucket and the Marketplace product that is subscribed are in the same region. 








