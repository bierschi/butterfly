pipeline {
         agent any
         stages {
                 stage('Build') {
                     steps {
                        echo 'Clean workspace ransomware'
                        cleanWs()
                     }
                     steps {
                         echo 'Build ransomware'
                         sh 'mkdir build'
                         dir ('build') {
                           sh 'cmake ..'
                           sh 'make'
                         }
                     }
                 }
                 stage('Test') {
                    steps {
                        echo 'Test ransomware'
                    }
                 }
                 stage('Deploy') {
                    steps {
                        echo "Deploy ransomware to target server"

                    }
                }
    }

}