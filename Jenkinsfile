pipeline {
    agent any
    stages {
        stage('Build UTs') { 
            steps {
                echo 'Building Unit Tests...'
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