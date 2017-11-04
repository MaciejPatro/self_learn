pipeline {
    agent any
    stages {
        stage('Build UTs') { 
            steps {
                echo 'Building Unit Tests...'
		sh 'cmake . -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++'
		sh 'make'
            }
        }
        stage('Running UTs') {
            steps {
                echo 'Running UTs'
                sh 'clang++ --version'
            }
        }
    }
}