pipeline {
    agent any
    stages {
        stage('AllTests'){
            agent {
                dockerfile true
            }
            steps {
                sh "cd ${env.WORKSPACE} && ./run_tests.sh"
            }
        }
    }
}