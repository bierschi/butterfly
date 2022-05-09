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
                        echo 'Testing butterfly units'
                        dir ('bin') {
                          sh './butterflyUnitTests'
                        }
                    }
                 }
                 stage('Install bflyServerApp') {
                    steps {
                        echo "Install bflyServerApp python package"
                        dir ('webserver') {
                          sh 'pip3 install -r requirements.txt'
                          sh 'python3 setup.py bdist_wheel'
                          sh 'sudo pip3 install dist/bflyServerApp-*-py3-none-any.whl'
                          sh 'sudo systemctl restart bflyServerApp.service'
                        }
                    }
                }
                 stage('Test Encryption') {
                    steps {
                        echo "Encrypting with butterfly"
                        dir ('bin') {
                          sh './butterfly --encrypt /home/christian/jenkins/butterfly_fs/'
                        }
                    }
                }
                 stage('Test Decryption') {
                    steps {
                        echo "Decrypting with butterfly"
                        dir ('bin') {
                          sh './butterfly --decrypt /home/christian/jenkins/butterfly_fs/'
                        }
                    }
                }
    }

}