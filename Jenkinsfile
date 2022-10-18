pipeline {
         agent any
         stages {
                 stage('Build Docker Images') {
                     steps {
                         echo 'Build Ubuntu Images'
                         dir ('docker/ubuntu') {
                           sh 'docker build -t ubuntu1804:butterfly -f Dockerfile.ubuntu1804 --build-arg CACHEBUST=$(date +%s) .'
                           sh 'docker build -t ubuntu2004:butterfly -f Dockerfile.ubuntu2004 --build-arg CACHEBUST=$(date +%s) .'
                           //sh 'docker build -t ubuntu2204:butterfly -f Dockerfile.ubuntu2204 --build-arg CACHEBUST=$(date +%s) .'
                         }
                         echo 'Build Debian Images'
                         dir ('docker/debian') {
                           sh 'docker build -t debian11:butterfly -f Dockerfile.debian --build-arg CACHEBUST=$(date +%s) .'
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
                          sh 'sudo systemctl restart b2bierschi-bflyServerApp.service'
                        }
                    }
                }
    }

}
