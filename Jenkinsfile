pipeline {
         agent any
         stages {

                 stage('Build') {
                     steps {
                         echo 'Build butterfly binary on test server'
                         sh 'mkdir build'
                         dir ('build') {
                           sh 'cmake -DCMAKE_TOOLCHAIN_FILE=../linux.cmake -DUNITTESTS=ON ../'
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

                 stage('Platform builds from develop') {

                    when {
                        expression { env.BRANCH_NAME == 'develop' }
                     }
                     steps {
                         echo 'Build Ubuntu Images from develop branch'
                         dir ('docker/ubuntu') {
                           sh 'docker build -t ubuntu1804:butterfly -f Dockerfile.ubuntu1804 --build-arg CACHEBUST=$(date +%s) --build-arg BRANCH=develop .'
                           sh 'docker build -t ubuntu2004:butterfly -f Dockerfile.ubuntu2004 --build-arg CACHEBUST=$(date +%s) --build-arg BRANCH=develop .'
                           sh 'docker build -t ubuntu2204:butterfly -f Dockerfile.ubuntu2204 --build-arg CACHEBUST=$(date +%s) --build-arg BRANCH=develop .'
                         }
                         echo 'Build Debian Images from develop branch'
                         dir ('docker/debian') {
                           sh 'docker build -t debian11:butterfly -f Dockerfile.debian11 --build-arg CACHEBUST=$(date +%s) --build-arg BRANCH=develop .'
                          }
                     }
                 }

                 stage('Platform builds from master') {

                    when {
                        expression { env.BRANCH_NAME == 'master' }
                     }
                     steps {
                         echo 'Build Ubuntu Images from master branch'
                         dir ('docker/ubuntu') {
                           sh 'docker build -t ubuntu1804:butterfly -f Dockerfile.ubuntu1804 --build-arg CACHEBUST=$(date +%s) --build-arg BRANCH=master .'
                           sh 'docker build -t ubuntu2004:butterfly -f Dockerfile.ubuntu2004 --build-arg CACHEBUST=$(date +%s) --build-arg BRANCH=master .'
                           sh 'docker build -t ubuntu2204:butterfly -f Dockerfile.ubuntu2204 --build-arg CACHEBUST=$(date +%s) --build-arg BRANCH=master .'
                         }
                         echo 'Build Debian Images from master branch'
                         dir ('docker/debian') {
                           sh 'docker build -t debian11:butterfly -f Dockerfile.debian11 --build-arg CACHEBUST=$(date +%s) --build-arg BRANCH=master .'
                          }
                     }
                 }

                 stage('Butterfly Encryption Test') {
                    steps {
                        echo "Encrypting the data folder"
                        dir ('bin') {
                          sh './butterfly --encrypt ../data/'
                        }
                    }
                }

                 stage('Butterfly Decryption Test') {
                    steps {
                        echo "Decrypting the data folder"
                        dir ('bin') {
                          sh './butterfly --decrypt ../data/'
                        }
                    }
                }

                 stage('Static Code Analysis') {
                    steps {
                        echo "Run cppcheck for butterfly project"
                        dir ('scripts') {
                          sh './cppcheck.sh --xml --html'
                        }
                    }
                 }

                 stage('Doxygen Docu') {
                    steps {
                        echo "Build Doxygen Docu for butterfly project"
                        dir ('docs') {
                          sh 'doxygen butterfly > /dev/null 2>&1'
                        }
                    }
                 }

                 stage('Reports') {
                    steps {
                        echo "Publish cppcheck reports"
                        publishCppcheck (
                        allowNoReport: true,
                        pattern: 'reports/cppcheck.xml'
                        )
                        echo "Build doxygen latex pdf reports"
                        dir ('docs/latex') {
                          sh 'make > /dev/null 2>&1'
                          sh 'mv refman.pdf butterfly.pdf'
                          sh 'mv butterfly.pdf ../../reports/'
                        }
                    }
                 }

                 stage('Deploy butterfly artifacts') {

                    when {
                        expression { "${env.GIT_BRANCH}" =~ "origin/release/*" }
                    }

                    steps {
                        echo "Deploy butterfly artifacts"
                    }
                }

                 stage('Install bflyServerApp') {

                    when {
                        expression { "${env.GIT_BRANCH}" =~ "release/*" }
                    }

                    steps {
                        echo "Install bflyServerApp python package"
                        dir ('webserver') {
                          sh 'pip3 install -r requirements.txt'
                          sh 'python3 setup.py bdist_wheel'
                          sh 'sudo pip3 install dist/bflyServerApp-*-py3-none-any.whl'
                          sh 'sudo systemctl restart b2bierschi-bflyServerApp.service'
                          archiveArtifacts (allowEmptyArchive: true,
                          artifacts: 'dist/*whl', fingerprint: true)
                        }
                    }
                }
    }

}
