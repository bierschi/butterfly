pipeline {
         agent any
         stages {
                 stage('Build') {
                     steps {
                         echo 'Build ransomware'
                         sh 'pwd'
                         sh 'mkdir build'
                         sh 'cd build'
                         sh 'cmake ..'
                         sh 'make'
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
         post {
            always {
                cleanWs()
            }
        }
}