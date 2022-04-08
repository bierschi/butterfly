pipeline {
         agent any
         stages {
                 stage('Build') {
                     steps {
                         echo 'Build butterfly'
                         sh 'mkdir build'
                         dir ('build') {
                           sh 'cmake ../ -DUNITTESTS=ON'
                           sh 'make'
                         }
                     }
                 }
                 stage('UnitTests') {
                    steps {
                        echo 'Test ransomware'
                        dir ('bin') {
                          sh './butterflyUnitTests'
                        }
                    }
                 }
                 stage('Test') {
                    steps {
                        echo "Test Encryption/Decryption of butterfly"
                    }
                }
    }

}