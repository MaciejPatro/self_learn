pipeline {
    agent any
    stages {
        stage('Build UTs') { 
            steps {
		sh 'cmake -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ .'
		sh 'make'
            }
        }
        stage('Running UTs') {
            steps {
                sh './self_learn_repo'
            }
        }
    }
}